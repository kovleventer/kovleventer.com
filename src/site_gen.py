import os
import yaml
from jinja2 import Environment, FileSystemLoader
import datetime

base_files = ["index", "about", "blog", "misc"]

if os.getcwd().split("/")[-1] == "src":
    srcprefix = "./"
    buildprefix = "../"
else:
    srcprefix = "src/"
    buildprefix = "./"


def get_blog_entries():
    blogdir = os.path.join(srcprefix, "blog/")
    dir_entries = [os.path.join(blogdir, o) for o in os.listdir(blogdir) if os.path.isdir(os.path.join(blogdir, o))]

    entries = []

    for entry in dir_entries:
        config = os.path.join(entry, "config.yml")
        if os.path.exists(config):
            with open(config) as f:
                cfg = yaml.load(f, Loader=yaml.SafeLoader)
                if cfg["published"]:
                    entries.append({"name": cfg['name'], "date": cfg['date'], "link": "blog/" + entry.split("/")[-1]})
        else:
            print("Warning: no config file found for", entry)

    return sorted(entries, key=lambda e : e['date'], reverse=True)


env = Environment(loader=FileSystemLoader(srcprefix))
for base_file in base_files:
    template = env.get_template(base_file + '.html')

    if base_file == "blog":
        entries = get_blog_entries()
        output_from_parsed_template = template.render(active=base_file, entries=entries)
    else:
        output_from_parsed_template = template.render(active=base_file)

    with open(buildprefix + "build/" + base_file + ".html", "w") as f:
        f.write(output_from_parsed_template)
