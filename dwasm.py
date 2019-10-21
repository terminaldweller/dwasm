#!/usr/bin/python3

import code
import signal
import sys
from parse import Argparser, premain, SigHandler_SIGINT,PythonInterpreter

def getWASMModule():
    module_path = sys.argv[1]
    interpreter = PythonInterpreter()
    #module = interpreter.parse(module_path)

def main():
    signal.signal(signal.SIGINT, SigHandler_SIGINT)
    argparser = Argparser()
    if argparser.args.dbg:
        try:
            premain(argparser)
        except Exception as e:
            print(e.__doc__)
            if e.message: print(e.message)
            variables = globals().copy()
            variables.update(locals())
            shell = code.InteractiveConsole(variables)
            shell.interact(banner="DEVIWASM REPL")
    else:
        premain(argparser)

if __name__ == "__main__":
    main()
