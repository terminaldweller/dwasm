
[![Total alerts](https://img.shields.io/lgtm/alerts/g/bloodstalker/dwasm.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/bloodstalker/dwasm/alerts/)

# dwasm
dwasm is a WASM dump tool.<br/>

## Requirements
dwasm is self-contained.<br/>

## Options
For a list of available options, just run `dwasm -h`. Here's a copy of what you'll get:<br/>

```bash
  -h, --help            show this help message and exit
  --wast WAST           path to the wasm text file
  --wasm WASM [WASM ...]
                        path to the wasm object file
  --asb ASB             path to the wast file to assemble
  --dis DIS             path to the wasm file to disassemble
  -o O                  the path to the output file
  --dbg                 print debug info
  --unval               skips validation tests
  --memdump MEMDUMP     dumps the linear memory
  --idxspc              print index space data
  --run                 runs the start function
  --metric              print metrics
  --gas                 print gas usage
  --entry ENTRY         name of the function that will act as the entry point
                        into execution
  --link LINK [LINK ...]
                        link the following wasm modules
  --sectiondump SECTIONDUMP
                        dumps the section provided
  --hexdump HEXDUMP     dumps all sections
  --dbgsection DBGSECTION
                        dumps the parsed section provided
  --interactive         open in cli mode
  --rawdump RAWDUMP RAWDUMP
                        dumps all sections
```
