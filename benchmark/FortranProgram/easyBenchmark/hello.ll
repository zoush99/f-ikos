; ModuleID = '/tmp/helloworld-af3797.ll'
source_filename = "/tmp/helloworld-af3797.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.C331_MAIN_ = internal constant i32 14
@.C336_MAIN_ = internal constant [11 x i8] c"Hello world"
@.C312_MAIN_ = internal constant i64 0
@.C335_MAIN_ = internal constant i32 6
@.C332_MAIN_ = internal constant [14 x i8] c"helloworld.f90"
@.C334_MAIN_ = internal constant i32 2
@.C311_MAIN_ = internal constant i32 0

define void @MAIN_() !dbg !5 {
L.entry:
  %z__io_338 = alloca i32, align 4
  call void (ptr, ...) @fort_init(ptr @.C311_MAIN_), !dbg !8
  br label %L.LB1_347

L.LB1_347:                                        ; preds = %L.entry
  call void (ptr, ptr, i64, ...) @f90io_src_info03a(ptr @.C334_MAIN_, ptr @.C332_MAIN_, i64 14), !dbg !9
  %0 = call i32 (ptr, ptr, ptr, ptr, ...) @f90io_print_init(ptr @.C335_MAIN_, ptr null, ptr @.C311_MAIN_, ptr @.C311_MAIN_), !dbg !9
  store i32 %0, ptr %z__io_338, align 4, !dbg !9
  %1 = call i32 (ptr, i32, i64, ...) @f90io_sc_ch_ldw(ptr @.C336_MAIN_, i32 14, i64 11), !dbg !9
  store i32 %1, ptr %z__io_338, align 4, !dbg !9
  %2 = call i32 (...) @f90io_ldw_end(), !dbg !9
  store i32 %2, ptr %z__io_338, align 4, !dbg !9
  call void (ptr, ptr, i64, ...) @f90_stop08a(ptr @.C311_MAIN_, ptr null, i64 0), !dbg !10
  ret void, !dbg !11
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
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm -S helloworld.f90 -o hello.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "helloworld.f90", directory: "/home/zou/Downloads/FortranProgram/easyBenchmark")
!4 = !{}
!5 = distinct !DISubprogram(name: "main", scope: !2, file: !3, line: 1, type: !6, scopeLine: 1, spFlags: DISPFlagDefinition | DISPFlagMainSubprogram, unit: !2, retainedNodes: !4)
!6 = !DISubroutineType(cc: DW_CC_program, types: !7)
!7 = !{null}
!8 = !DILocation(line: 1, column: 1, scope: !5)
!9 = !DILocation(line: 2, column: 1, scope: !5)
!10 = !DILocation(line: 3, column: 1, scope: !5)
!11 = !DILocation(line: 4, column: 1, scope: !5)
