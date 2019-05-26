cmake_minimum_required(VERSION 3.8)

project(Compiler)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION FALSE)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")


include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})


set(CMAKE_CXX_STANDARD 17)


add_executable(Compiler Absyn.C Absyn.H Lexer.C Parser.H Parser.C Printer.C Printer.H Skeleton.C Skeleton.H Test.C)

# Find the libraries that correspond to the LLVM components
# that we wish to use
llvm_map_components_to_libnames(llvm_libs
        support asmparser core irreader codegen asmprinter  AVRAsmPrinter AVRAsmParser
        X86AsmPrinter X86AsmParser WebAssemblyAsmParser WebAssemblyAsmPrinter SparcAsmParser SparcAsmPrinter MSP430AsmParser MSP430AsmPrinter
        PowerPCAsmParser PowerPCAsmPrinter MipsAsmParser MipsAsmPrinter LanaiAsmParser LanaiAsmPrinter SystemZAsmParser SystemZAsmPrinter BPFAsmParser BPFAsmPrinter ARMAsmParser ARMAsmPrinter
        HexagonAsmParser AMDGPUAsmParser AMDGPUAsmPrinter AArch64AsmParser AArch64AsmPrinter NVPTXAsmPrinter

        AVRCodeGen AVRDesc AVRDisassembler AVRInfo
        XCoreCodeGen XCoreDesc XCoreDisassembler XCoreInfo
        X86CodeGen X86Desc X86Disassembler
        WebAssemblyCodeGen WebAssemblyDesc WebAssemblyDisassembler WebAssemblyInfo
        SystemZCodeGen SystemZDesc SystemZDisassembler
        SparcCodeGen SparcDesc SparcDisassembler
        PowerPCCodeGen PowerPCDesc PowerPCDisassembler
        NVPTXCodeGen NVPTXDesc
        MSP430Codegen MSP430Desc
        MipsCodegen MipsDesc
        LanaiCodegen LanaiDesc
        HexagonCodegen HexagonDesc
        BPFCodegen BPFDesc
        ARMCodegen ARMDesc
        AMDGPUCodegen AMDGPUDesc
        AArch64Codegen AArch64Desc
        )

# Link against LLVM libraries
target_link_libraries(Compiler ${llvm_libs})
