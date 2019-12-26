import http.server
import socketserver
import os

PORT = 8000
# https://stackoverflow.com/questions/39801718/how-to-run-a-http-server-which-serves-a-specific-path
web_dir = os.path.join(os.path.dirname(__file__), 'build')
os.chdir(web_dir)

Handler = http.server.SimpleHTTPRequestHandler
httpd = socketserver.TCPServer(("", PORT), Handler)
print("Serving at http://localhost:" + str(PORT))
httpd.serve_forever()
