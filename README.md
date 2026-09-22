# CSE-306: Computer Architecture

Course assignments and projects for **CSE-306 Computer Architecture**, covering MIPS processor design, simulation, and implementation.

## Repository Structure

```
├── 01-alu/                    # ALU — Atmel Studio project (ATMega32 simulation)
├── 02-control-unit/           # Control Unit — Atmel Studio project
├── 03-data-memory/            # Data Memory — Atmel Studio project
├── 04-instruction-memory/     # Instruction Memory — Atmel Studio project
├── 05-register-file/          # Register File — Atmel Studio project
├── 06-assembler/              # MIPS Assembler (C++ & shell script)
├── 07-group-project/          # Group 6 — Complete MIPS circuits & documentation
│   ├── docs/                  # Assignment PDFs & presentations
│   ├── *.circ                 # Logisim circuit files
│   └── ...
├── 08-4bit-mips-cpu/          # 4-bit MIPS CPU — Proteus simulation & submission
│   ├── A2_4__Submission/      # Final submission (report + simulation + ATMega32 files)
│   └── ...
├── 09-proteus-backups/        # Proteus simulation backup
├── misc/                      # Standalone circuit files & utilities
│   ├── 7400-lib.circ          # 7400-series IC library for Logisim
│   ├── ALU.circ               # Standalone ALU circuit
│   ├── fpa.cpp                # Floating-point adder implementation
│   └── ...
└── tools/                     # Simulation tools
    ├── logisim/               # Logisim 2.7.1 (JAR)
    └── logisim-evolution/     # Logisim Evolution 3.7.2 (JAR)
```

## Tools Required

- **[Logisim](http://www.cburch.com/logisim/)** 2.7.1 — Digital circuit simulator (included in `tools/`)
- **[Logisim Evolution](https://github.com/logisim-evolution/logisim-evolution)** 3.7.2 — Extended Logisim fork (included in `tools/`)
- **[Atmel Studio](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio)** — For ATMega32 simulation projects
- **[Proteus](https://www.labcenter.com/)** — For circuit simulation (`.pdsprj` files)
- **Java 8+** — Required to run Logisim JARs
- **G++** — For compiling the assembler and FPA

## Quick Start

### Run Logisim circuits
```bash
java -jar tools/logisim/logisim-generic-2.7.1.jar
# Open any .circ file from the GUI
```

### Run the assembler
```bash
cd 06-assembler
bash run_assembler.sh
```

### Compile the floating-point adder
```bash
g++ misc/fpa.cpp -o fpa
./fpa < misc/fpa_test.txt
```
