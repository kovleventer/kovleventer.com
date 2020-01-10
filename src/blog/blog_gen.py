import os
import sys
from jinja2 import Environment, FileSystemLoader
import yaml

from pygments import highlight
from pygments.formatters.html import HtmlFormatter
from pygments.lexers import guess_lexer

import matplotlib
import matplotlib.pyplot as plt
from matplotlib.offsetbox import AnchoredOffsetbox, TextArea, HPacker
from io import BytesIO

folder = sys.argv[1]


def syntax_file(filename):
    filename = os.path.join(folder, filename)
    content = open(filename).read()
    return highlight(content, guess_lexer(content), HtmlFormatter(cssclass="code_highlight"))

matplotlib.rcParams['text.usetex'] = True
def render_tex(filename, fontsize=24, amsmath=True):
    matplotlib.rcParams['text.latex.preamble'] = r'\usepackage{amsmath}' if amsmath else '' # amsmath fucks up integral signs
    filename = os.path.join(folder, filename)
    content = open(filename).read()[:-1] # New line at the end
    fig = plt.figure(figsize=(0.01, 0.01))
    fig.text(0, 0, content, fontsize=fontsize)

    svg = filename.replace("src", "build")
    svg = svg.replace(".tex", ".svg")
    fig.savefig(svg, dpi=300,
                transparent=True,
                format='svg',
                bbox_inches='tight',
                pad_inches=0.1,
                frameon=False
                )
    plt.close(fig)

    svg = svg.split("/")[-1]
    return '<img class="formula" src="' + svg + '">'


config = os.path.join(folder, "config.yaml")
html = os.path.join(folder, "index.html")

with open(config) as f:
    cfg = yaml.load(f)
    title = cfg["name"]

env = Environment(loader=FileSystemLoader("src"))
template = env.get_template(html.replace("src/", ""))

output_from_parsed_template = template.render(active="blog", title=title, code=syntax_file, formula=render_tex)

with open(html.replace("src", "build"), "w") as f:
    f.write(output_from_parsed_template)
