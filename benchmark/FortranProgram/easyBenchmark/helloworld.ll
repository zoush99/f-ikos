; ModuleID = '/tmp/helloworld-7ff1a1.ll'
source_filename = "/tmp/helloworld-7ff1a1.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.C330_main_ = internal constant i32 14
@.C335_main_ = internal constant [11 x i8] c"Hello world"
@.C309_main_ = internal constant i32 0
@.C310_main_ = internal constant i64 0
@.C334_main_ = internal constant i32 6
@.C331_main_ = internal constant [14 x i8] c"helloworld.f90"
@.C333_main_ = internal constant i32 2

define signext i32 @main_() !dbg !5 {
L.entry:
  %z__io_337 = alloca i32, align 4
  %main_329 = alloca i32, align 4
  br label %L.LB1_344

L.LB1_344:                                        ; preds = %L.entry
  %0 = bitcast i32* @.C333_main_ to i8*, !dbg !9
  %1 = bitcast [14 x i8]* @.C331_main_ to i8*, !dbg !9
  %2 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !9
  call void (i8*, i8*, i64, ...) %2(i8* %0, i8* %1, i64 14), !dbg !9
  %3 = bitcast i32* @.C334_main_ to i8*, !dbg !9
  %4 = bitcast i32* @.C309_main_ to i8*, !dbg !9
  %5 = bitcast i32* @.C309_main_ to i8*, !dbg !9
  %6 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !9
  %7 = call i32 (i8*, i8*, i8*, i8*, ...) %6(i8* %3, i8* null, i8* %4, i8* %5), !dbg !9
  store i32 %7, i32* %z__io_337, align 4, !dbg !9
  %8 = bitcast [11 x i8]* @.C335_main_ to i8*, !dbg !9
  %9 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !9
  %10 = call i32 (i8*, i32, i64, ...) %9(i8* %8, i32 14, i64 11), !dbg !9
  store i32 %10, i32* %z__io_337, align 4, !dbg !9
  %11 = call i32 (...) @f90io_ldw_end(), !dbg !9
  store i32 %11, i32* %z__io_337, align 4, !dbg !9
  %12 = bitcast i32* @.C309_main_ to i8*, !dbg !10
  %13 = bitcast void (...)* @f90_stop08a to void (i8*, i8*, i64, ...)*, !dbg !10
  call void (i8*, i8*, i64, ...) %13(i8* %12, i8* null, i64 0), !dbg !10
  %14 = load i32, i32* %main_329, align 4, !dbg !11
  ret i32 %14, !dbg !11
}

declare void @f90_stop08a(...)

declare signext i32 @f90io_ldw_end(...)

declare signext i32 @f90io_sc_ch_ldw(...)

declare signext i32 @f90io_print_init(...)

declare void @f90io_src_info03a(...)

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm -S helloworld.f90 -o helloworld.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "helloworld.f90", directory: "/home/zou/Downloads/FortranProgram/easyBenchmark")
!4 = !{}
!5 = distinct !DISubprogram(name: "main", scope: !2, file: !3, line: 1, type: !6, scopeLine: 1, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!6 = !DISubroutineType(types: !7)
!7 = !{!8}
!8 = !DIBasicType(name: "integer", size: 32, align: 32, encoding: DW_ATE_signed)
!9 = !DILocation(line: 2, column: 1, scope: !5)
!10 = !DILocation(line: 3, column: 1, scope: !5)
!11 = !DILocation(line: 4, column: 1, scope: !5)
