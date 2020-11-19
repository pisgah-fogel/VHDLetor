
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
        print("[.] Parsing %s ..." % self.vhdlFile)
        print("[.] Writing to %s ..." % self.hppFile)
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
            line_count = -1
            for line in vhdfile:
                # Insert ' ' after and before special characters
                buff = ""
                for i in range(len(line)):
                    flag = False
                    if line[i] in ['(', ')', '[', ']', '{', '}', '&', '^', '|', '=', ':', ';', '<', '>', '+', '-', ',']:
                        flag = True
                    if flag:
                        buff += " "
                    buff += line[i]
                    if flag:
                        buff += " "
                line = buff
                print(line)
                line_count += 1
                splited = line.split(" ")
                self.data["ignored"] = []
                self.data["tmp_signal"] = []
                for word in splited:
                    if state == "module name":
                        # TODO: check if name is valid
                        self.data["module"] = word
                        state = "module wait ("
                    elif state == "module wait (":
                        if word == "(":
                            state = "module declaration"
                    elif state == "module declaration":
                        if word == ")":
                            state = "module wait ;"
                            # TODO: save signal if needed
                        if len(self.data["tmp_signal"]) == 0:
                            if word == "input" or word == "output":
                                if "input" in self.data["tmp_signal"] or "output" in self.data["tmp_signal"]:
                                    print("Error ",self.vhdlFile,":",line_count," : input/output has already been set for this signal")
                                self.data["tmp_signal"].append(word)
                            elif word == "wire" or word == "reg":
                                if "wire" in self.data["tmp_signal"] or "reg" in self.data["tmp_signal"]:
                                    print("Error ",self.vhdlFile,":",line_count," : wire/reg has already been set for this signal")
                                self.data["tmp_signal"].append(word)
                            elif word == ",":
                                # TODO: save signal if needed
                                pass
                            elif not "signal name" in self.data:
                                self.data["signal name"] = word
                    elif state == "module wait ;":
                        if word == ";":
                            state = "module body"
                        else:
                            print("Error ",self.vhdlFile,":",line_count," : Expected ';' after module's declaration")
                    elif state == "module body":
                        pass
                        # TODO
                    elif word == "module":
                        state = "module name"
                    else:
                        if state == "module wait (":
                            print("Error ",self.vhdlFile,":",line_count," : Expected '(' after module's name")
                        self.data["ignored"].append(splited)
        print(self.data)

