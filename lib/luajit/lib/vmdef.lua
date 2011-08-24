-- This is a generated file. DO NOT EDIT!

module(...)

bcnames = "ISLT  ISGE  ISLE  ISGT  ISEQV ISNEV ISEQS ISNES ISEQN ISNEN ISEQP ISNEP ISTC  ISFC  IST   ISF   MOV   NOT   UNM   LEN   ADDVN SUBVN MULVN DIVVN MODVN ADDNV SUBNV MULNV DIVNV MODNV ADDVV SUBVV MULVV DIVVV MODVV POW   CAT   KSTR  KCDATAKSHORTKNUM  KPRI  KNIL  UGET  USETV USETS USETN USETP UCLO  FNEW  TNEW  TDUP  GGET  GSET  TGETV TGETS TGETB TSETV TSETS TSETB TSETM CALLM CALL  CALLMTCALLT ITERC ITERN VARG  ISNEXTRETM  RET   RET0  RET1  FORI  JFORI FORL  IFORL JFORL ITERL IITERLJITERLLOOP  ILOOP JLOOP JMP   FUNCF IFUNCFJFUNCFFUNCV IFUNCVJFUNCVFUNCC FUNCCW"

irnames = "LT    GE    LE    GT    ULT   UGE   ULE   UGT   EQ    NE    ABC   RETF  NOP   BASE  HIOP  LOOP  USE   PHI   RENAMEKPRI  KINT  KGC   KPTR  KKPTR KNULL KNUM  KINT64KSLOT BNOT  BSWAP BAND  BOR   BXOR  BSHL  BSHR  BSAR  BROL  BROR  ADD   SUB   MUL   DIV   MOD   POW   NEG   ABS   ATAN2 LDEXP MIN   MAX   FPMATHADDOV SUBOV MULOV AREF  HREFK HREF  NEWREFUREFO UREFC FREF  STRREFALOAD HLOAD ULOAD FLOAD XLOAD SLOAD VLOAD ASTOREHSTOREUSTOREFSTOREXSTORESNEW  XSNEW TNEW  TDUP  CNEW  CNEWI TBAR  OBAR  XBAR  CONV  TOBIT TOSTR STRTO CALLN CALLL CALLS CALLXSCARG  "

irfpm = { [0]="floor", "ceil", "trunc", "sqrt", "exp", "exp2", "log", "log2", "log10", "sin", "cos", "tan", "other", }

irfield = { [0]="str.len", "func.env", "tab.meta", "tab.array", "tab.node", "tab.asize", "tab.hmask", "tab.nomm", "udata.meta", "udata.udtype", "udata.file", "cdata.typeid", "cdata.ptr", "cdata.int64", "cdata.int64hi", }

ircall = {
[0]="lj_str_cmp",
"lj_str_new",
"lj_str_tonum",
"lj_str_fromint",
"lj_str_fromnum",
"lj_tab_new1",
"lj_tab_dup",
"lj_tab_newkey",
"lj_tab_len",
"lj_gc_step_jit",
"lj_gc_barrieruv",
"lj_mem_newgco",
"lj_math_random_step",
"lj_vm_modi",
"lj_carith_divi64",
"lj_carith_divu64",
"lj_carith_modi64",
"lj_carith_modu64",
"lj_carith_powi64",
"lj_carith_powu64",
"lj_cdata_setfin",
"strlen",
"memcpy",
"memset",
"sinh",
"cosh",
"tanh",
"fputc",
"fwrite",
"fflush",
}

traceerr = {
[0]="error thrown or hook called during recording",
"trace too long",
"trace too deep",
"too many snapshots",
"blacklisted",
"NYI: bytecode %d",
"leaving loop in root trace",
"inner loop in root trace",
"loop unroll limit reached",
"bad argument type",
"call to JIT-disabled function",
"call unroll limit reached",
"down-recursion, restarting",
"NYI: C function %p",
"NYI: FastFunc %s",
"NYI: unsupported variant of FastFunc %s",
"NYI: return to lower frame",
"store with nil or NaN key",
"missing metamethod",
"looping index lookup",
"NYI: mixed sparse/dense table",
"symbol not in cache",
"NYI: unsupported C type conversion",
"NYI: unsupported C function type",
"guard would always fail",
"too many PHIs",
"persistent type instability",
"failed to allocate mcode memory",
"machine code too long",
"hit mcode limit (retrying)",
"too many spill slots",
"inconsistent register allocation",
"NYI: cannot assemble IR instruction %d",
"NYI: PHI shuffling too complex",
"NYI: register coalescing too complex",
}

ffnames = {
[0]="Lua",
"C",
"assert",
"type",
"getmetatable",
"setmetatable",
"getfenv",
"setfenv",
"rawget",
"rawset",
"rawequal",
"unpack",
"select",
"tonumber",
"tostring",
"next",
"pairs",
"ipairs_aux",
"ipairs",
"error",
"pcall",
"xpcall",
"loadstring",
"loadfile",
"load",
"dofile",
"gcinfo",
"collectgarbage",
"newproxy",
"print",
"coroutine.status",
"coroutine.running",
"coroutine.create",
"coroutine.yield",
"coroutine.resume",
"coroutine.wrap_aux",
"coroutine.wrap",
"math.abs",
"math.floor",
"math.ceil",
"math.sqrt",
"math.log",
"math.log10",
"math.exp",
"math.sin",
"math.cos",
"math.tan",
"math.asin",
"math.acos",
"math.atan",
"math.sinh",
"math.cosh",
"math.tanh",
"math.frexp",
"math.modf",
"math.deg",
"math.rad",
"math.atan2",
"math.pow",
"math.fmod",
"math.ldexp",
"math.min",
"math.max",
"math.random",
"math.randomseed",
"bit.tobit",
"bit.bnot",
"bit.bswap",
"bit.lshift",
"bit.rshift",
"bit.arshift",
"bit.rol",
"bit.ror",
"bit.band",
"bit.bor",
"bit.bxor",
"bit.tohex",
"string.len",
"string.byte",
"string.char",
"string.sub",
"string.rep",
"string.reverse",
"string.lower",
"string.upper",
"string.dump",
"string.find",
"string.match",
"string.gmatch_aux",
"string.gmatch",
"string.gsub",
"string.format",
"table.foreachi",
"table.foreach",
"table.getn",
"table.maxn",
"table.insert",
"table.remove",
"table.concat",
"table.sort",
"io.method.close",
"io.method.read",
"io.method.write",
"io.method.flush",
"io.method.seek",
"io.method.setvbuf",
"io.method.lines",
"io.method.__gc",
"io.method.__tostring",
"io.open",
"io.popen",
"io.tmpfile",
"io.close",
"io.read",
"io.write",
"io.flush",
"io.input",
"io.output",
"io.lines_iter",
"io.lines",
"io.type",
"os.execute",
"os.remove",
"os.rename",
"os.tmpname",
"os.getenv",
"os.exit",
"os.clock",
"os.date",
"os.time",
"os.difftime",
"os.setlocale",
"debug.getregistry",
"debug.getmetatable",
"debug.setmetatable",
"debug.getfenv",
"debug.setfenv",
"debug.getinfo",
"debug.getlocal",
"debug.setlocal",
"debug.getupvalue",
"debug.setupvalue",
"debug.sethook",
"debug.gethook",
"debug.debug",
"debug.traceback",
"jit.on",
"jit.off",
"jit.flush",
"jit.status",
"jit.attach",
"jit.util.funcinfo",
"jit.util.funcbc",
"jit.util.funck",
"jit.util.funcuvname",
"jit.util.traceinfo",
"jit.util.traceir",
"jit.util.tracek",
"jit.util.tracesnap",
"jit.util.tracemc",
"jit.util.traceexitstub",
"jit.util.ircalladdr",
"jit.opt.start",
"ffi.meta.__index",
"ffi.meta.__newindex",
"ffi.meta.__eq",
"ffi.meta.__len",
"ffi.meta.__lt",
"ffi.meta.__le",
"ffi.meta.__concat",
"ffi.meta.__call",
"ffi.meta.__add",
"ffi.meta.__sub",
"ffi.meta.__mul",
"ffi.meta.__div",
"ffi.meta.__mod",
"ffi.meta.__pow",
"ffi.meta.__unm",
"ffi.meta.__tostring",
"ffi.clib.__index",
"ffi.clib.__newindex",
"ffi.clib.__gc",
"ffi.cdef",
"ffi.new",
"ffi.cast",
"ffi.typeof",
"ffi.istype",
"ffi.sizeof",
"ffi.alignof",
"ffi.offsetof",
"ffi.errno",
"ffi.string",
"ffi.copy",
"ffi.fill",
"ffi.abi",
"ffi.metatype",
"ffi.gc",
"ffi.load",
}

