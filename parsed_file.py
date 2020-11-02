
class ParsedFile:
    def init(self):
        self.data = {}
        self.langage = []
        self.hppFile = []
        self.vhdlFile = []
    def setLangage(self, lang):
        self.langage = lang
    def setHppFile(self, filename):
        self.hppFile = filename
    def setVHDLFile(self, filename):
        self.vhdlFile = filename
    def parse(self):
        print("[.] Parsing %s..." % self.vhdlFile)
        print("[.] Writing to %s..." % self.hppFile)
        if self.langage == "VHDL":
            self.parseVHDL()
        elif self.langage == "Verilog":
            self.parseVerilog()
        else:
            print("[x] Error: ParsedFile::parse langage not suppprrted")
            exit(1)
    def parseVHDL(self):
        print("[x] VHDL parser is not implemented yet") # TODO
        exit(1)
    def parseVerilog(self):
        print("[.] Parsing Verilog...")
        state = ""
        with open(self.vhdlFile, "r") as vhdfile:
            for line in vhdfile:
                splited = line.split(" ")
                for word in splitted:
                    if state == "module name":
                        # TODO: check if name is valid
                        data["module"] = word
                        state = "module wait ("
                    elif word == "module":
                        state = "module name"

