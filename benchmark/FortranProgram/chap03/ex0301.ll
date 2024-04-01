; ModuleID = '/tmp/ex0301-0b76c3.ll'
source_filename = "/tmp/ex0301-0b76c3.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.C340_MAIN_ = internal constant i32 4
@.C338_MAIN_ = internal constant i32 14
@.C333_MAIN_ = internal constant [5 x i8] c"Hello"
@.C310_MAIN_ = internal constant i64 0
@.C332_MAIN_ = internal constant i32 6
@.C329_MAIN_ = internal constant [10 x i8] c"ex0301.for"
@.C331_MAIN_ = internal constant i32 3
@.C309_MAIN_ = internal constant i32 0

define void @MAIN_() !dbg !5 {
L.entry:
  %z__io_335 = alloca i32, align 4
  %0 = bitcast i32* @.C309_MAIN_ to i8*
  %1 = bitcast void (...)* @fort_init to void (i8*, ...)*
  call void (i8*, ...) %1(i8* %0)
  br label %L.LB1_346

L.LB1_346:                                        ; preds = %L.entry
  %2 = bitcast i32* @.C331_MAIN_ to i8*, !dbg !8
  %3 = bitcast [10 x i8]* @.C329_MAIN_ to i8*, !dbg !8
  %4 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !8
  call void (i8*, i8*, i64, ...) %4(i8* %2, i8* %3, i64 10), !dbg !8
  %5 = bitcast i32* @.C332_MAIN_ to i8*, !dbg !8
  %6 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !8
  %7 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !8
  %8 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !8
  %9 = call i32 (i8*, i8*, i8*, i8*, ...) %8(i8* %5, i8* null, i8* %6, i8* %7), !dbg !8
  store i32 %9, i32* %z__io_335, align 4, !dbg !8
  %10 = bitcast [5 x i8]* @.C333_MAIN_ to i8*, !dbg !8
  %11 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !8
  %12 = call i32 (i8*, i32, i64, ...) %11(i8* %10, i32 14, i64 5), !dbg !8
  store i32 %12, i32* %z__io_335, align 4, !dbg !8
  %13 = call i32 (...) @f90io_ldw_end(), !dbg !8
  store i32 %13, i32* %z__io_335, align 4, !dbg !8
  %14 = bitcast i32* @.C340_MAIN_ to i8*, !dbg !9
  %15 = bitcast [10 x i8]* @.C329_MAIN_ to i8*, !dbg !9
  %16 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !9
  call void (i8*, i8*, i64, ...) %16(i8* %14, i8* %15, i64 10), !dbg !9
  %17 = bitcast i32* @.C332_MAIN_ to i8*, !dbg !9
  %18 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !9
  %19 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !9
  %20 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !9
  %21 = call i32 (i8*, i8*, i8*, i8*, ...) %20(i8* %17, i8* null, i8* %18, i8* %19), !dbg !9
  store i32 %21, i32* %z__io_335, align 4, !dbg !9
  %22 = bitcast [5 x i8]* @.C333_MAIN_ to i8*, !dbg !9
  %23 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !9
  %24 = call i32 (i8*, i32, i64, ...) %23(i8* %22, i32 14, i64 5), !dbg !9
  store i32 %24, i32* %z__io_335, align 4, !dbg !9
  %25 = call i32 (...) @f90io_ldw_end(), !dbg !9
  store i32 %25, i32* %z__io_335, align 4, !dbg !9
  %26 = bitcast i32* @.C332_MAIN_ to i8*, !dbg !10
  %27 = bitcast [10 x i8]* @.C329_MAIN_ to i8*, !dbg !10
  %28 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !10
  call void (i8*, i8*, i64, ...) %28(i8* %26, i8* %27, i64 10), !dbg !10
  %29 = bitcast i32* @.C332_MAIN_ to i8*, !dbg !10
  %30 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !10
  %31 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !10
  %32 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !10
  %33 = call i32 (i8*, i8*, i8*, i8*, ...) %32(i8* %29, i8* null, i8* %30, i8* %31), !dbg !10
  store i32 %33, i32* %z__io_335, align 4, !dbg !10
  %34 = bitcast [5 x i8]* @.C333_MAIN_ to i8*, !dbg !10
  %35 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !10
  %36 = call i32 (i8*, i32, i64, ...) %35(i8* %34, i32 14, i64 5), !dbg !10
  store i32 %36, i32* %z__io_335, align 4, !dbg !10
  %37 = call i32 (...) @f90io_ldw_end(), !dbg !10
  store i32 %37, i32* %z__io_335, align 4, !dbg !10
  %38 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !11
  %39 = bitcast void (...)* @f90_stop08a to void (i8*, i8*, i64, ...)*, !dbg !11
  call void (i8*, i8*, i64, ...) %39(i8* %38, i8* null, i64 0), !dbg !11
  ret void, !dbg !12
}

declare void @f90_stop08a(...)

declare signext i32 @f90io_ldw_end(...)

declare signext i32 @f90io_sc_ch_ldw(...)

declare signext i32 @f90io_print_init(...)

declare void @f90io_src_info03a(...)

declare void @fort_init(...)

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm -S -c ex0301.for -o ex0301.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "ex0301.for", directory: "/home/zou/Downloads/FortranProgram/chap03")
!4 = !{}
!5 = distinct !DISubprogram(name: "main", scope: !2, file: !3, line: 2, type: !6, scopeLine: 2, spFlags: DISPFlagDefinition | DISPFlagMainSubprogram, unit: !2, retainedNodes: !4)
!6 = !DISubroutineType(cc: DW_CC_program, types: !7)
!7 = !{null}
!8 = !DILocation(line: 3, column: 1, scope: !5)
!9 = !DILocation(line: 4, column: 1, scope: !5)
!10 = !DILocation(line: 6, column: 1, scope: !5)
!11 = !DILocation(line: 7, column: 1, scope: !5)
!12 = !DILocation(line: 8, column: 1, scope: !5)
