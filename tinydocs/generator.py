# @module generator
import json
from pathlib import Path
from jinja2 import Environment, FileSystemLoader

# @class SiteGenerator
# @desc Converts the TinyDocs JSON output into a searchable HTML static site.
class SiteGenerator:
    def __init__(self, json_path: str, output_dir: str = "docs"):
        self.json_path = Path(json_path)
        self.output_dir = Path(output_dir)
        self.env = Environment(loader=FileSystemLoader('tinydocs/templates'))

    # @method generate
    # @desc Reads the JSON file and renders the Jinja2 template.
    def generate(self):
        if not self.json_path.exists():
            raise FileNotFoundError(f"Could not find {self.json_path}")

        with open(self.json_path, 'r') as f:
            data = json.load(f)

        # Create output directory
        self.output_dir.mkdir(parents=True, exist_ok=True)

        # Render the template
        template = self.env.get_template('index.html.j2')
        output_html = template.render(
            timestamp=data.get("timestamp"),
            files=data.get("docs", [])
        )

        with open(self.output_dir / "index.html", "w") as f:
            f.write(output_html)
        
        print(f"Site generated successfully at {self.output_dir}/index.html")
