; ModuleID = '/tmp/test-ed63b4.ll'
source_filename = "/tmp/test-ed63b4.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.C345_add_ = internal constant i32 25
@.C343_add_ = internal constant i32 14
@.C338_add_ = internal constant [12 x i8] c"2.5+3.0/2.0="
@.C310_add_ = internal constant i64 0
@.C337_add_ = internal constant i32 6
@.C334_add_ = internal constant [8 x i8] c"test.f90"
@.C336_add_ = internal constant i32 10
@.C333_add_ = internal constant i32 3
@.C309_add_ = internal constant i32 0

define float @add_(i64* %x) !dbg !5 {
L.entry:
  %b_332 = alloca i32, align 4
  %a_331 = alloca i32, align 4
  %z__io_340 = alloca i32, align 4
  %add_330 = alloca float, align 4
  br label %L.LB1_350

L.LB1_350:                                        ; preds = %L.entry
  store i32 0, i32* %b_332, align 4, !dbg !9
  store i32 3, i32* %a_331, align 4, !dbg !10
  %0 = bitcast i32* @.C336_add_ to i8*, !dbg !11
  %1 = bitcast [8 x i8]* @.C334_add_ to i8*, !dbg !11
  %2 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !11
  call void (i8*, i8*, i64, ...) %2(i8* %0, i8* %1, i64 8), !dbg !11
  %3 = bitcast i32* @.C337_add_ to i8*, !dbg !11
  %4 = bitcast i32* @.C309_add_ to i8*, !dbg !11
  %5 = bitcast i32* @.C309_add_ to i8*, !dbg !11
  %6 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !11
  %7 = call i32 (i8*, i8*, i8*, i8*, ...) %6(i8* %3, i8* null, i8* %4, i8* %5), !dbg !11
  store i32 %7, i32* %z__io_340, align 4, !dbg !11
  %8 = bitcast [12 x i8]* @.C338_add_ to i8*, !dbg !11
  %9 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !11
  %10 = call i32 (i8*, i32, i64, ...) %9(i8* %8, i32 14, i64 12), !dbg !11
  store i32 %10, i32* %z__io_340, align 4, !dbg !11
  %11 = load i32, i32* %a_331, align 4, !dbg !11
  %12 = bitcast i32 (...)* @f90io_sc_i_ldw to i32 (i32, i32, ...)*, !dbg !11
  %13 = call i32 (i32, i32, ...) %12(i32 %11, i32 25), !dbg !11
  store i32 %13, i32* %z__io_340, align 4, !dbg !11
  %14 = call i32 (...) @f90io_ldw_end(), !dbg !11
  store i32 %14, i32* %z__io_340, align 4, !dbg !11
  %15 = load i32, i32* %a_331, align 4, !dbg !12
  %16 = load i32, i32* %b_332, align 4, !dbg !12
  %17 = sdiv i32 %15, %16, !dbg !12
  store i32 %17, i32* %a_331, align 4, !dbg !12
  %18 = load float, float* %add_330, align 4, !dbg !13
  ret float %18, !dbg !13
}

declare signext i32 @f90io_ldw_end(...)

declare signext i32 @f90io_sc_i_ldw(...)

declare signext i32 @f90io_sc_ch_ldw(...)

declare signext i32 @f90io_print_init(...)

declare void @f90io_src_info03a(...)

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm -c -S test.f90 -o test.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "test.f90", directory: "/home/zou/Documents/f-ikos/benchmark")
!4 = !{}
!5 = distinct !DISubprogram(name: "add", scope: !2, file: !3, line: 3, type: !6, scopeLine: 3, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!6 = !DISubroutineType(types: !7)
!7 = !{!8, !8}
!8 = !DIBasicType(name: "real", size: 32, align: 32, encoding: DW_ATE_float)
!9 = !DILocation(line: 8, column: 1, scope: !5)
!10 = !DILocation(line: 9, column: 1, scope: !5)
!11 = !DILocation(line: 10, column: 1, scope: !5)
!12 = !DILocation(line: 11, column: 1, scope: !5)
!13 = !DILocation(line: 12, column: 1, scope: !5)
