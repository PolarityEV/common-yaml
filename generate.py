#!/usr/bin/env python3
"""
Polarity Error Code Generator

Generates language-specific error code files from a single YAML definition.
Supports: C, Dart (Flutter), and can be extended for other languages.

Usage:
    python generate.py [--output-dir OUTPUT_DIR]

Requirements:
    pip install pyyaml jinja2
"""

import argparse
import os
import sys
from datetime import datetime
from pathlib import Path

try:
    import yaml
    from jinja2 import Environment, FileSystemLoader, select_autoescape
except ImportError:
    print("Error: Required packages not installed.")
    print("Please run: pip install pyyaml jinja2")
    sys.exit(1)


def to_camel_case(snake_str):
    """Convert snake_case to camelCase."""
    components = snake_str.split('_')
    # First component lowercase, rest title case
    return components[0].lower() + ''.join(x.title() for x in components[1:])


def load_definitions(yaml_path):
    """Load error definitions from YAML file."""
    with open(yaml_path, 'r') as f:
        return yaml.safe_load(f)


def generate_c_header(definitions, output_path, template_env):
    """Generate C header file."""
    template = template_env.get_template('c_header.j2')

    # Prepare data for template
    all_errors = []
    for category_name, category_data in definitions['categories'].items():
        for error in category_data['errors']:
            all_errors.append({
                'category': category_name,
                'category_desc': category_data['description'],
                'name': error['name'],
                'code': error['code'],
                'description': error['description'],
                'severity': error.get('severity', 'error')
            })

    content = template.render(
        project_name=definitions['project_name'],
        prefix=definitions['prefix'],
        version=definitions['version'],
        categories=definitions['categories'],
        all_errors=all_errors,
        legacy_mapping=definitions.get('legacy_mapping', {}),
        generated_date=datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    )

    with open(output_path, 'w') as f:
        f.write(content)
    print(f"✓ Generated C header: {output_path}")


def generate_dart_file(definitions, output_path, template_env):
    """Generate Dart class file."""
    template = template_env.get_template('dart.j2')

    # Prepare data for template
    all_errors = []
    error_map = {}  # code -> description mapping

    for category_name, category_data in definitions['categories'].items():
        for error in category_data['errors']:
            dart_name = to_camel_case(error['name'])
            all_errors.append({
                'category': category_name,
                'category_desc': category_data['description'],
                'name': error['name'],
                'dart_name': dart_name,
                'code': error['code'],
                'description': error['description'],
                'severity': error.get('severity', 'error')
            })
            error_map[error['code']] = error['description']

    content = template.render(
        project_name=definitions['project_name'],
        prefix=definitions['prefix'],
        version=definitions['version'],
        categories=definitions['categories'],
        all_errors=all_errors,
        error_map=error_map,
        generated_date=datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    )

    with open(output_path, 'w') as f:
        f.write(content)
    print(f"✓ Generated Dart file: {output_path}")


def main():
    parser = argparse.ArgumentParser(
        description='Generate error code files from YAML definitions'
    )
    parser.add_argument(
        '--output-dir',
        default='generated',
        help='Output directory for generated files (default: generated/)'
    )
    args = parser.parse_args()

    # Paths
    script_dir = Path(__file__).parent
    definitions_path = script_dir / 'definitions.yaml'
    templates_dir = script_dir / 'templates'
    output_dir = Path(args.output_dir)

    # Check if definitions file exists
    if not definitions_path.exists():
        print(f"Error: definitions.yaml not found at {definitions_path}")
        sys.exit(1)

    # Check if templates directory exists
    if not templates_dir.exists():
        print(f"Error: templates directory not found at {templates_dir}")
        sys.exit(1)

    # Create output directory
    output_dir.mkdir(parents=True, exist_ok=True)

    # Load definitions
    print(f"Loading definitions from {definitions_path}...")
    definitions = load_definitions(definitions_path)

    # Setup Jinja2 environment
    template_env = Environment(
        loader=FileSystemLoader(templates_dir),
        autoescape=select_autoescape(),
        trim_blocks=True,
        lstrip_blocks=True
    )

    # Generate files
    print("\nGenerating error code files...")

    # C header
    c_output = output_dir / 'polarity_errors.h'
    generate_c_header(definitions, c_output, template_env)

    # Dart file
    dart_output = output_dir / 'polarity_errors.dart'
    generate_dart_file(definitions, dart_output, template_env)

    print(f"\n✓ All files generated successfully in {output_dir}/")
    print("\nNext steps:")
    print("  1. Copy generated files to your project")
    print("  2. Update #include statements to use new header")
    print("  3. Test the integration")


if __name__ == '__main__':
    main()
