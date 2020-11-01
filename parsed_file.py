
class ParsedFile:
    def init(self):
        self.libraries = []
    def setHppFile(self, filename):
        self.hppFile = filename
    def setVHDLFile(self, filename):
        self.vhdlFile = filename
    def parse(self):
        print("[.] Parsing %s..." % self.vhdlFile)
        print("[.] Writing to %s..." % self.hppFile)
