import os
import sys
from jinja2 import Environment, FileSystemLoader
import yaml

folder = sys.argv[1]

config = os.path.join(folder, "config.yaml")
html = os.path.join(folder, "index.html")

with open(config) as f:
    cfg = yaml.load(f)
    title = cfg["name"]

env = Environment(loader=FileSystemLoader("src"))
template = env.get_template(html.replace("src/", ""))

output_from_parsed_template = template.render(active="blog", title=title)

with open(html.replace("src", "build"), "w") as f:
    f.write(output_from_parsed_template)
