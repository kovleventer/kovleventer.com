import os
import sys
from jinja2 import Environment, FileSystemLoader
import yaml
from xml.dom import minidom

from pygments import highlight
from pygments.formatters.html import HtmlFormatter
from pygments.lexers import guess_lexer, get_lexer_by_name
from pygments.filters import NameHighlightFilter
from pygments.token import Literal

import matplotlib
import matplotlib.pyplot as plt
from matplotlib.offsetbox import AnchoredOffsetbox, TextArea, HPacker
from io import BytesIO

folder = sys.argv[1]



def syntax_file(filename, lang_name="", filtered_words=None):
    filename = os.path.join(folder, filename)
    content = open(filename).read()
    if not lang_name:
        lexer = guess_lexer(content)
    else:
        lexer = get_lexer_by_name(lang_name)
    #if filtered_words:
        #lexer.add_filter(NameHighlightFilter(names=filtered_words), tokentype=Literal)
        # TODO make this work
    return highlight(content, lexer, HtmlFormatter(cssclass="code_highlight"))

def render_tex_mathjax(filename, fontsize=24, inline=False, amsmath=False):
    filename = os.path.join(folder, filename)
    content = open(filename).read()[1:-2]  # New line at the end and the $ signs TODO this should be handled better
    svg = filename.replace("src", "build")
    svg = svg.replace(".tex", ".svg")
    os.system("node src/lib/tex2svg.js '" + content + "' > " + svg)
    dom = minidom.parse(svg)
    new_size = float(dom.getElementsByTagName('svg')[0].getAttribute("width")[:-2])
    new_size = int(new_size * fontsize * 0.555)
    svg = svg.split("/")[-1]
    return '<img style="width: ' + str(new_size) + 'px" class="formula' + (' inline"' if inline else '"') + ' src="' + svg + '">'

# DEPRECATED
plt.rc('mathtext', fontset='cm')
matplotlib.rcParams['text.usetex'] = True
def render_tex_matplotlib(filename, fontsize=24, amsmath=True, inline=False):
    matplotlib.rcParams['text.latex.preamble'] = r'\usepackage{amsmath}\usepackage{xcolor}' if amsmath else '' # amsmath fucks up integral signs (and fracs as well)
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
                pad_inches=0.0,
                frameon=False
                )
    plt.close(fig)

    svg = svg.split("/")[-1]
    return '<img class="formula' + (' inline"' if inline else '"') + ' src="' + svg + '">'


config = os.path.join(folder, "config.yml")
html = os.path.join(folder, "index.html")

with open(config) as f:
    cfg = yaml.load(f, Loader=yaml.SafeLoader)
    title = cfg["name"]

env = Environment(loader=FileSystemLoader("src"))
template = env.get_template(html.replace("src/", ""))

output_from_parsed_template = template.render(active="blog", title=title,
                                              code=syntax_file,
                                              formula=render_tex_mathjax,)

with open(html.replace("src", "build"), "w") as f:
    f.write(output_from_parsed_template)
