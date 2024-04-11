; ModuleID = '/tmp/bisect-ad5ff8.ll'
source_filename = "/tmp/bisect-ad5ff8.ll"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.C313_numerical_bisect_ = internal constant float 0.000000e+00
@.C329_numerical_bisect_ = internal constant float 0x3EE4F8B580000000
@.C315_numerical_bisect_ = internal constant float 2.000000e+00
@.C332_numerical_f1_ = internal constant float 3.000000e+00
@.C333_numerical_f2_ = internal constant float 5.000000e+00
@.C332_numerical_f2_ = internal constant float 4.000000e+00
@.C378_MAIN_ = internal constant i32 83
@.C377_MAIN_ = internal constant i32 78
@.C375_MAIN_ = internal constant i32 75
@.C374_MAIN_ = internal constant i32 74
@.C367_MAIN_ = internal constant [11 x i8] c"('x=',F6.3)"
@.C366_MAIN_ = internal constant i32 71
@.C365_MAIN_ = internal constant [12 x i8] c"\B2\BB\D5\FD\C8\B7\B5\C4\B2\C2\D6\B5"
@.C364_MAIN_ = internal constant i32 66
@.C313_MAIN_ = internal constant float 0.000000e+00
@.C311_MAIN_ = internal constant i32 1
@.C361_MAIN_ = internal constant i32 27
@.C358_MAIN_ = internal constant i32 5
@.C357_MAIN_ = internal constant i32 63
@.C350_MAIN_ = internal constant i32 14
@.C351_MAIN_ = internal constant [14 x i8] c"\CA\E4\C8\EB\C1\BD\B8\F6\B2\C2\B2\E2\D6\B5"
@.C310_MAIN_ = internal constant i64 0
@.C349_MAIN_ = internal constant i32 6
@.C346_MAIN_ = internal constant [10 x i8] c"bisect.f90"
@.C348_MAIN_ = internal constant i32 62
@.C309_MAIN_ = internal constant i32 0

; Function Attrs: noinline
define i32 @numerical_() #0 {
.L.entry:
  ret i32 undef
}

define float @numerical_bisect_(i64* %a, i64* %b, i64* %func, i64* %"func$sd") !dbg !5 {
L.entry:
  %c_335 = alloca float, align 4
  %fc_338 = alloca float, align 4
  %fa_336 = alloca float, align 4
  %fb_337 = alloca float, align 4
  %bisect_334 = alloca float, align 4
  br label %L.LB2_351

L.LB2_351:                                        ; preds = %L.entry
  %0 = bitcast i64* %b to float*, !dbg !14
  %1 = load float, float* %0, align 4, !dbg !14
  %2 = bitcast i64* %a to float*, !dbg !14
  %3 = load float, float* %2, align 4, !dbg !14
  %4 = fadd float %1, %3, !dbg !14
  %5 = fdiv float %4, 2.000000e+00, !dbg !14
  store float %5, float* %c_335, align 4, !dbg !14
  %6 = bitcast float* %c_335 to i8*, !dbg !15
  %7 = bitcast i64* %func to float (i8*, ...)*, !dbg !15
  %8 = call float (i8*, ...) %7(i8* %6), !dbg !15
  store float %8, float* %fc_338, align 4, !dbg !15
  br label %L.LB2_339

L.LB2_339:                                        ; preds = %L.LB2_346, %L.LB2_351
  %9 = load float, float* %fc_338, align 4, !dbg !16
  %10 = call float @llvm.fabs.f32(float %9), !dbg !16
  %11 = fcmp ule float %10, 0x3EE4F8B580000000, !dbg !16
  br i1 %11, label %L.LB2_344, label %L.LB2_362, !dbg !16

L.LB2_362:                                        ; preds = %L.LB2_339
  %12 = bitcast i64* %a to i8*, !dbg !17
  %13 = bitcast i64* %func to float (i8*, ...)*, !dbg !17
  %14 = call float (i8*, ...) %13(i8* %12), !dbg !17
  store float %14, float* %fa_336, align 4, !dbg !17
  %15 = bitcast i64* %b to i8*, !dbg !18
  %16 = bitcast i64* %func to float (i8*, ...)*, !dbg !18
  %17 = call float (i8*, ...) %16(i8* %15), !dbg !18
  store float %17, float* %fb_337, align 4, !dbg !18
  %18 = load float, float* %fc_338, align 4, !dbg !19
  %19 = load float, float* %fa_336, align 4, !dbg !19
  %20 = fmul float %18, %19, !dbg !19
  %21 = fcmp uge float %20, 0.000000e+00, !dbg !19
  br i1 %21, label %L.LB2_345, label %L.LB2_363, !dbg !19

L.LB2_363:                                        ; preds = %L.LB2_362
  %22 = load float, float* %c_335, align 4, !dbg !20
  %23 = bitcast i64* %b to float*, !dbg !20
  store float %22, float* %23, align 4, !dbg !20
  %24 = bitcast i64* %b to float*, !dbg !21
  %25 = load float, float* %24, align 4, !dbg !21
  %26 = bitcast i64* %a to float*, !dbg !21
  %27 = load float, float* %26, align 4, !dbg !21
  %28 = fadd float %25, %27, !dbg !21
  %29 = fdiv float %28, 2.000000e+00, !dbg !21
  store float %29, float* %c_335, align 4, !dbg !21
  br label %L.LB2_346, !dbg !22

L.LB2_345:                                        ; preds = %L.LB2_362
  %30 = load float, float* %c_335, align 4, !dbg !23
  %31 = bitcast i64* %a to float*, !dbg !23
  store float %30, float* %31, align 4, !dbg !23
  %32 = bitcast i64* %b to float*, !dbg !24
  %33 = load float, float* %32, align 4, !dbg !24
  %34 = bitcast i64* %a to float*, !dbg !24
  %35 = load float, float* %34, align 4, !dbg !24
  %36 = fadd float %33, %35, !dbg !24
  %37 = fdiv float %36, 2.000000e+00, !dbg !24
  store float %37, float* %c_335, align 4, !dbg !24
  br label %L.LB2_346

L.LB2_346:                                        ; preds = %L.LB2_345, %L.LB2_363
  %38 = bitcast float* %c_335 to i8*, !dbg !25
  %39 = bitcast i64* %func to float (i8*, ...)*, !dbg !25
  %40 = call float (i8*, ...) %39(i8* %38), !dbg !25
  store float %40, float* %fc_338, align 4, !dbg !25
  br label %L.LB2_339, !dbg !26

L.LB2_344:                                        ; preds = %L.LB2_339
  %41 = load float, float* %c_335, align 4, !dbg !27
  store float %41, float* %bisect_334, align 4, !dbg !27
  br label %L.LB2_342, !dbg !28

L.LB2_342:                                        ; preds = %L.LB2_344
  %42 = load float, float* %bisect_334, align 4, !dbg !29
  ret float %42, !dbg !29
}

define float @numerical_f1_(i64* %x) !dbg !30 {
L.entry:
  %f1_331 = alloca float, align 4
  br label %L.LB3_336

L.LB3_336:                                        ; preds = %L.entry
  %0 = bitcast i64* %x to float*, !dbg !33
  %1 = load float, float* %0, align 4, !dbg !33
  %2 = fsub float %1, 3.000000e+00, !dbg !33
  %3 = bitcast i64* %x to float*, !dbg !33
  %4 = load float, float* %3, align 4, !dbg !33
  %5 = fadd float %4, 3.000000e+00, !dbg !33
  %6 = fmul float %2, %5, !dbg !33
  store float %6, float* %f1_331, align 4, !dbg !33
  br label %L.LB3_333, !dbg !34

L.LB3_333:                                        ; preds = %L.LB3_336
  %7 = load float, float* %f1_331, align 4, !dbg !35
  ret float %7, !dbg !35
}

define float @numerical_f2_(i64* %x) !dbg !36 {
L.entry:
  %f2_331 = alloca float, align 4
  br label %L.LB4_337

L.LB4_337:                                        ; preds = %L.entry
  %0 = bitcast i64* %x to float*, !dbg !37
  %1 = load float, float* %0, align 4, !dbg !37
  %2 = fsub float %1, 5.000000e+00, !dbg !37
  %3 = bitcast i64* %x to float*, !dbg !37
  %4 = load float, float* %3, align 4, !dbg !37
  %5 = fadd float %4, 4.000000e+00, !dbg !37
  %6 = fmul float %2, %5, !dbg !37
  store float %6, float* %f2_331, align 4, !dbg !37
  br label %L.LB4_334, !dbg !38

L.LB4_334:                                        ; preds = %L.LB4_337
  %7 = load float, float* %f2_331, align 4, !dbg !39
  ret float %7, !dbg !39
}

define void @MAIN_() !dbg !40 {
L.entry:
  %z__io_353 = alloca i32, align 4
  %a_341 = alloca float, align 4
  %b_342 = alloca float, align 4
  %"z_d_0$sd_382" = alloca [10 x i64], align 8
  %ans_343 = alloca float, align 4
  %"z_d_1$sd_383" = alloca [10 x i64], align 8
  %0 = bitcast i32* @.C309_MAIN_ to i8*
  %1 = bitcast void (...)* @fort_init to void (i8*, ...)*
  call void (i8*, ...) %1(i8* %0)
  br label %L.LB5_392

L.LB5_392:                                        ; preds = %L.entry
  br label %L.LB5_344

L.LB5_344:                                        ; preds = %L.LB5_387, %L.LB5_392
  %2 = bitcast i32* @.C348_MAIN_ to i8*, !dbg !43
  %3 = bitcast [10 x i8]* @.C346_MAIN_ to i8*, !dbg !43
  %4 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !43
  call void (i8*, i8*, i64, ...) %4(i8* %2, i8* %3, i64 10), !dbg !43
  %5 = bitcast i32* @.C349_MAIN_ to i8*, !dbg !43
  %6 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !43
  %7 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !43
  %8 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !43
  %9 = call i32 (i8*, i8*, i8*, i8*, ...) %8(i8* %5, i8* null, i8* %6, i8* %7), !dbg !43
  store i32 %9, i32* %z__io_353, align 4, !dbg !43
  %10 = bitcast [14 x i8]* @.C351_MAIN_ to i8*, !dbg !43
  %11 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !43
  %12 = call i32 (i8*, i32, i64, ...) %11(i8* %10, i32 14, i64 14), !dbg !43
  store i32 %12, i32* %z__io_353, align 4, !dbg !43
  %13 = call i32 (...) @f90io_ldw_end(), !dbg !43
  store i32 %13, i32* %z__io_353, align 4, !dbg !43
  %14 = bitcast i32* @.C357_MAIN_ to i8*, !dbg !44
  %15 = bitcast [10 x i8]* @.C346_MAIN_ to i8*, !dbg !44
  %16 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !44
  call void (i8*, i8*, i64, ...) %16(i8* %14, i8* %15, i64 10), !dbg !44
  %17 = bitcast i32* @.C358_MAIN_ to i8*, !dbg !44
  %18 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !44
  %19 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !44
  %20 = bitcast i32 (...)* @f90io_ldr_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !44
  %21 = call i32 (i8*, i8*, i8*, i8*, ...) %20(i8* %17, i8* null, i8* %18, i8* %19), !dbg !44
  store i32 %21, i32* %z__io_353, align 4, !dbg !44
  %22 = bitcast i32* @.C361_MAIN_ to i8*, !dbg !44
  %23 = bitcast i32* @.C311_MAIN_ to i8*, !dbg !44
  %24 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !44
  %25 = bitcast float* %a_341 to i8*, !dbg !44
  %26 = bitcast i32 (...)* @f90io_ldra to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !44
  %27 = call i32 (i8*, i8*, i8*, i8*, ...) %26(i8* %22, i8* %23, i8* %24, i8* %25), !dbg !44
  store i32 %27, i32* %z__io_353, align 4, !dbg !44
  %28 = bitcast i32* @.C361_MAIN_ to i8*, !dbg !44
  %29 = bitcast i32* @.C311_MAIN_ to i8*, !dbg !44
  %30 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !44
  %31 = bitcast float* %b_342 to i8*, !dbg !44
  %32 = bitcast i32 (...)* @f90io_ldra to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !44
  %33 = call i32 (i8*, i8*, i8*, i8*, ...) %32(i8* %28, i8* %29, i8* %30, i8* %31), !dbg !44
  store i32 %33, i32* %z__io_353, align 4, !dbg !44
  %34 = call i32 (...) @f90io_ldr_end(), !dbg !44
  store i32 %34, i32* %z__io_353, align 4, !dbg !44
  %35 = bitcast float* %b_342 to i64*, !dbg !45
  %36 = call float @numerical_f1_(i64* %35), !dbg !45
  %37 = bitcast float* %a_341 to i64*, !dbg !45
  %38 = call float @numerical_f1_(i64* %37), !dbg !45
  %39 = fmul float %36, %38, !dbg !45
  %40 = fcmp uge float %39, 0.000000e+00, !dbg !45
  br i1 %40, label %L.LB5_387, label %L.LB5_427, !dbg !45

L.LB5_427:                                        ; preds = %L.LB5_344
  br label %L.LB5_363, !dbg !45

L.LB5_387:                                        ; preds = %L.LB5_344
  %41 = bitcast i32* @.C364_MAIN_ to i8*, !dbg !46
  %42 = bitcast [10 x i8]* @.C346_MAIN_ to i8*, !dbg !46
  %43 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !46
  call void (i8*, i8*, i64, ...) %43(i8* %41, i8* %42, i64 10), !dbg !46
  %44 = bitcast i32* @.C349_MAIN_ to i8*, !dbg !46
  %45 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !46
  %46 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !46
  %47 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !46
  %48 = call i32 (i8*, i8*, i8*, i8*, ...) %47(i8* %44, i8* null, i8* %45, i8* %46), !dbg !46
  store i32 %48, i32* %z__io_353, align 4, !dbg !46
  %49 = bitcast [12 x i8]* @.C365_MAIN_ to i8*, !dbg !46
  %50 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !46
  %51 = call i32 (i8*, i32, i64, ...) %50(i8* %49, i32 14, i64 12), !dbg !46
  store i32 %51, i32* %z__io_353, align 4, !dbg !46
  %52 = call i32 (...) @f90io_ldw_end(), !dbg !46
  store i32 %52, i32* %z__io_353, align 4, !dbg !46
  br label %L.LB5_344, !dbg !47

L.LB5_363:                                        ; preds = %L.LB5_427
  %53 = bitcast float* %a_341 to i64*, !dbg !48
  %54 = bitcast float* %b_342 to i64*, !dbg !48
  %55 = bitcast float (i64*)* @numerical_f1_ to i64*, !dbg !48
  %56 = bitcast [10 x i64]* %"z_d_0$sd_382" to i64*, !dbg !48
  %57 = call float @numerical_bisect_(i64* %53, i64* %54, i64* %55, i64* %56), !dbg !48
  store float %57, float* %ans_343, align 4, !dbg !48
  %58 = bitcast i32* @.C366_MAIN_ to i8*, !dbg !49
  %59 = bitcast [10 x i8]* @.C346_MAIN_ to i8*, !dbg !49
  %60 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !49
  call void (i8*, i8*, i64, ...) %60(i8* %58, i8* %59, i64 10), !dbg !49
  %61 = bitcast i32* @.C350_MAIN_ to i8*, !dbg !49
  %62 = bitcast i32* @.C311_MAIN_ to i8*, !dbg !49
  %63 = bitcast [11 x i8]* @.C367_MAIN_ to i8*, !dbg !49
  %64 = bitcast i32 (...)* @f90io_encode_fmta to i32 (i8*, i8*, i8*, i64, ...)*, !dbg !49
  %65 = call i32 (i8*, i8*, i8*, i64, ...) %64(i8* %61, i8* %62, i8* %63, i64 11), !dbg !49
  store i32 %65, i32* %z__io_353, align 4, !dbg !49
  %66 = bitcast i32* @.C349_MAIN_ to i8*, !dbg !49
  %67 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !49
  %68 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !49
  %69 = bitcast i32 (...)* @f90io_fmtw_inita to i32 (i8*, i8*, i8*, i8*, i8*, i8*, i64, ...)*, !dbg !49
  %70 = call i32 (i8*, i8*, i8*, i8*, i8*, i8*, i64, ...) %69(i8* %66, i8* null, i8* %67, i8* %68, i8* null, i8* null, i64 0), !dbg !49
  store i32 %70, i32* %z__io_353, align 4, !dbg !49
  %71 = load float, float* %ans_343, align 4, !dbg !49
  %72 = bitcast i32 (...)* @f90io_sc_f_fmt_write to i32 (float, i32, ...)*, !dbg !49
  %73 = call i32 (float, i32, ...) %72(float %71, i32 27), !dbg !49
  store i32 %73, i32* %z__io_353, align 4, !dbg !49
  %74 = call i32 (...) @f90io_fmtw_end(), !dbg !49
  store i32 %74, i32* %z__io_353, align 4, !dbg !49
  br label %L.LB5_373

L.LB5_373:                                        ; preds = %L.LB5_389, %L.LB5_363
  %75 = bitcast i32* @.C374_MAIN_ to i8*, !dbg !50
  %76 = bitcast [10 x i8]* @.C346_MAIN_ to i8*, !dbg !50
  %77 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !50
  call void (i8*, i8*, i64, ...) %77(i8* %75, i8* %76, i64 10), !dbg !50
  %78 = bitcast i32* @.C349_MAIN_ to i8*, !dbg !50
  %79 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !50
  %80 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !50
  %81 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !50
  %82 = call i32 (i8*, i8*, i8*, i8*, ...) %81(i8* %78, i8* null, i8* %79, i8* %80), !dbg !50
  store i32 %82, i32* %z__io_353, align 4, !dbg !50
  %83 = bitcast [14 x i8]* @.C351_MAIN_ to i8*, !dbg !50
  %84 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !50
  %85 = call i32 (i8*, i32, i64, ...) %84(i8* %83, i32 14, i64 14), !dbg !50
  store i32 %85, i32* %z__io_353, align 4, !dbg !50
  %86 = call i32 (...) @f90io_ldw_end(), !dbg !50
  store i32 %86, i32* %z__io_353, align 4, !dbg !50
  %87 = bitcast i32* @.C375_MAIN_ to i8*, !dbg !51
  %88 = bitcast [10 x i8]* @.C346_MAIN_ to i8*, !dbg !51
  %89 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !51
  call void (i8*, i8*, i64, ...) %89(i8* %87, i8* %88, i64 10), !dbg !51
  %90 = bitcast i32* @.C358_MAIN_ to i8*, !dbg !51
  %91 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !51
  %92 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !51
  %93 = bitcast i32 (...)* @f90io_ldr_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !51
  %94 = call i32 (i8*, i8*, i8*, i8*, ...) %93(i8* %90, i8* null, i8* %91, i8* %92), !dbg !51
  store i32 %94, i32* %z__io_353, align 4, !dbg !51
  %95 = bitcast i32* @.C361_MAIN_ to i8*, !dbg !51
  %96 = bitcast i32* @.C311_MAIN_ to i8*, !dbg !51
  %97 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !51
  %98 = bitcast float* %a_341 to i8*, !dbg !51
  %99 = bitcast i32 (...)* @f90io_ldra to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !51
  %100 = call i32 (i8*, i8*, i8*, i8*, ...) %99(i8* %95, i8* %96, i8* %97, i8* %98), !dbg !51
  store i32 %100, i32* %z__io_353, align 4, !dbg !51
  %101 = bitcast i32* @.C361_MAIN_ to i8*, !dbg !51
  %102 = bitcast i32* @.C311_MAIN_ to i8*, !dbg !51
  %103 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !51
  %104 = bitcast float* %b_342 to i8*, !dbg !51
  %105 = bitcast i32 (...)* @f90io_ldra to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !51
  %106 = call i32 (i8*, i8*, i8*, i8*, ...) %105(i8* %101, i8* %102, i8* %103, i8* %104), !dbg !51
  store i32 %106, i32* %z__io_353, align 4, !dbg !51
  %107 = call i32 (...) @f90io_ldr_end(), !dbg !51
  store i32 %107, i32* %z__io_353, align 4, !dbg !51
  %108 = bitcast float* %b_342 to i64*, !dbg !52
  %109 = call float @numerical_f2_(i64* %108), !dbg !52
  %110 = bitcast float* %a_341 to i64*, !dbg !52
  %111 = call float @numerical_f2_(i64* %110), !dbg !52
  %112 = fmul float %109, %111, !dbg !52
  %113 = fcmp uge float %112, 0.000000e+00, !dbg !52
  br i1 %113, label %L.LB5_389, label %L.LB5_428, !dbg !52

L.LB5_428:                                        ; preds = %L.LB5_373
  br label %L.LB5_376, !dbg !52

L.LB5_389:                                        ; preds = %L.LB5_373
  %114 = bitcast i32* @.C377_MAIN_ to i8*, !dbg !53
  %115 = bitcast [10 x i8]* @.C346_MAIN_ to i8*, !dbg !53
  %116 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !53
  call void (i8*, i8*, i64, ...) %116(i8* %114, i8* %115, i64 10), !dbg !53
  %117 = bitcast i32* @.C349_MAIN_ to i8*, !dbg !53
  %118 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !53
  %119 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !53
  %120 = bitcast i32 (...)* @f90io_print_init to i32 (i8*, i8*, i8*, i8*, ...)*, !dbg !53
  %121 = call i32 (i8*, i8*, i8*, i8*, ...) %120(i8* %117, i8* null, i8* %118, i8* %119), !dbg !53
  store i32 %121, i32* %z__io_353, align 4, !dbg !53
  %122 = bitcast [12 x i8]* @.C365_MAIN_ to i8*, !dbg !53
  %123 = bitcast i32 (...)* @f90io_sc_ch_ldw to i32 (i8*, i32, i64, ...)*, !dbg !53
  %124 = call i32 (i8*, i32, i64, ...) %123(i8* %122, i32 14, i64 12), !dbg !53
  store i32 %124, i32* %z__io_353, align 4, !dbg !53
  %125 = call i32 (...) @f90io_ldw_end(), !dbg !53
  store i32 %125, i32* %z__io_353, align 4, !dbg !53
  br label %L.LB5_373, !dbg !54

L.LB5_376:                                        ; preds = %L.LB5_428
  %126 = bitcast float* %a_341 to i64*, !dbg !55
  %127 = bitcast float* %b_342 to i64*, !dbg !55
  %128 = bitcast float (i64*)* @numerical_f2_ to i64*, !dbg !55
  %129 = bitcast [10 x i64]* %"z_d_1$sd_383" to i64*, !dbg !55
  %130 = call float @numerical_bisect_(i64* %126, i64* %127, i64* %128, i64* %129), !dbg !55
  store float %130, float* %ans_343, align 4, !dbg !55
  %131 = bitcast i32* @.C378_MAIN_ to i8*, !dbg !56
  %132 = bitcast [10 x i8]* @.C346_MAIN_ to i8*, !dbg !56
  %133 = bitcast void (...)* @f90io_src_info03a to void (i8*, i8*, i64, ...)*, !dbg !56
  call void (i8*, i8*, i64, ...) %133(i8* %131, i8* %132, i64 10), !dbg !56
  %134 = bitcast i32* @.C350_MAIN_ to i8*, !dbg !56
  %135 = bitcast i32* @.C311_MAIN_ to i8*, !dbg !56
  %136 = bitcast [11 x i8]* @.C367_MAIN_ to i8*, !dbg !56
  %137 = bitcast i32 (...)* @f90io_encode_fmta to i32 (i8*, i8*, i8*, i64, ...)*, !dbg !56
  %138 = call i32 (i8*, i8*, i8*, i64, ...) %137(i8* %134, i8* %135, i8* %136, i64 11), !dbg !56
  store i32 %138, i32* %z__io_353, align 4, !dbg !56
  %139 = bitcast i32* @.C349_MAIN_ to i8*, !dbg !56
  %140 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !56
  %141 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !56
  %142 = bitcast i32 (...)* @f90io_fmtw_inita to i32 (i8*, i8*, i8*, i8*, i8*, i8*, i64, ...)*, !dbg !56
  %143 = call i32 (i8*, i8*, i8*, i8*, i8*, i8*, i64, ...) %142(i8* %139, i8* null, i8* %140, i8* %141, i8* null, i8* null, i64 0), !dbg !56
  store i32 %143, i32* %z__io_353, align 4, !dbg !56
  %144 = load float, float* %ans_343, align 4, !dbg !56
  %145 = bitcast i32 (...)* @f90io_sc_f_fmt_write to i32 (float, i32, ...)*, !dbg !56
  %146 = call i32 (float, i32, ...) %145(float %144, i32 27), !dbg !56
  store i32 %146, i32* %z__io_353, align 4, !dbg !56
  %147 = call i32 (...) @f90io_fmtw_end(), !dbg !56
  store i32 %147, i32* %z__io_353, align 4, !dbg !56
  %148 = bitcast i32* @.C309_MAIN_ to i8*, !dbg !57
  %149 = bitcast void (...)* @f90_stop08a to void (i8*, i8*, i64, ...)*, !dbg !57
  call void (i8*, i8*, i64, ...) %149(i8* %148, i8* null, i64 0), !dbg !57
  ret void, !dbg !58
}

declare void @f90_stop08a(...)

declare signext i32 @f90io_fmtw_end(...)

declare signext i32 @f90io_sc_f_fmt_write(...)

declare signext i32 @f90io_fmtw_inita(...)

declare signext i32 @f90io_encode_fmta(...)

declare signext i32 @f90io_ldr_end(...)

declare signext i32 @f90io_ldra(...)

declare signext i32 @f90io_ldr_init(...)

declare signext i32 @f90io_ldw_end(...)

declare signext i32 @f90io_sc_ch_ldw(...)

declare signext i32 @f90io_print_init(...)

declare void @f90io_src_info03a(...)

declare void @fort_init(...)

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare float @llvm.fabs.f32(float) #1

attributes #0 = { noinline }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.module.flags = !{!0, !1}
!llvm.dbg.cu = !{!2}

!0 = !{i32 2, !"Dwarf Version", i32 4}
!1 = !{i32 2, !"Debug Info Version", i32 3}
!2 = distinct !DICompileUnit(language: DW_LANG_Fortran90, file: !3, producer: " F90 Flang - 1.5 2017-05-01", isOptimized: false, flags: "'+flang -emit-llvm -S -c bisect.f90 -o bisect.ll'", runtimeVersion: 0, emissionKind: FullDebug, enums: !4, retainedTypes: !4, globals: !4, imports: !4, nameTableKind: None)
!3 = !DIFile(filename: "bisect.f90", directory: "/home/zou/Documents/f-ikos/benchmark/FortranProByzou/Fortran 95\E7\A8\8B\E5\BA\8F\E8\AE\BE\E8\AE\A1")
!4 = !{}
!5 = distinct !DISubprogram(name: "bisect", scope: !6, file: !3, line: 7, type: !7, scopeLine: 7, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!6 = !DIModule(scope: !2, name: "numerical", file: !3)
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !9, !9, !9, !10}
!9 = !DIBasicType(name: "real", size: 32, align: 32, encoding: DW_ATE_float)
!10 = !DICompositeType(tag: DW_TAG_array_type, baseType: !11, size: 640, align: 64, elements: !12)
!11 = !DIBasicType(name: "integer*8", size: 64, align: 64, encoding: DW_ATE_signed)
!12 = !{!13}
!13 = !DISubrange(lowerBound: 1, upperBound: 10)
!14 = !DILocation(line: 17, column: 1, scope: !5)
!15 = !DILocation(line: 18, column: 1, scope: !5)
!16 = !DILocation(line: 21, column: 1, scope: !5)
!17 = !DILocation(line: 22, column: 1, scope: !5)
!18 = !DILocation(line: 23, column: 1, scope: !5)
!19 = !DILocation(line: 24, column: 1, scope: !5)
!20 = !DILocation(line: 26, column: 1, scope: !5)
!21 = !DILocation(line: 27, column: 1, scope: !5)
!22 = !DILocation(line: 28, column: 1, scope: !5)
!23 = !DILocation(line: 30, column: 1, scope: !5)
!24 = !DILocation(line: 31, column: 1, scope: !5)
!25 = !DILocation(line: 34, column: 1, scope: !5)
!26 = !DILocation(line: 35, column: 1, scope: !5)
!27 = !DILocation(line: 36, column: 1, scope: !5)
!28 = !DILocation(line: 37, column: 1, scope: !5)
!29 = !DILocation(line: 38, column: 1, scope: !5)
!30 = distinct !DISubprogram(name: "f1", scope: !6, file: !3, line: 40, type: !31, scopeLine: 40, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!31 = !DISubroutineType(types: !32)
!32 = !{!9, !9}
!33 = !DILocation(line: 43, column: 1, scope: !30)
!34 = !DILocation(line: 44, column: 1, scope: !30)
!35 = !DILocation(line: 45, column: 1, scope: !30)
!36 = distinct !DISubprogram(name: "f2", scope: !6, file: !3, line: 47, type: !31, scopeLine: 47, spFlags: DISPFlagDefinition, unit: !2, retainedNodes: !4)
!37 = !DILocation(line: 50, column: 1, scope: !36)
!38 = !DILocation(line: 51, column: 1, scope: !36)
!39 = !DILocation(line: 52, column: 1, scope: !36)
!40 = distinct !DISubprogram(name: "main", scope: !2, file: !3, line: 56, type: !41, scopeLine: 56, spFlags: DISPFlagDefinition | DISPFlagMainSubprogram, unit: !2, retainedNodes: !4)
!41 = !DISubroutineType(cc: DW_CC_program, types: !42)
!42 = !{null}
!43 = !DILocation(line: 62, column: 1, scope: !40)
!44 = !DILocation(line: 63, column: 1, scope: !40)
!45 = !DILocation(line: 65, column: 1, scope: !40)
!46 = !DILocation(line: 66, column: 1, scope: !40)
!47 = !DILocation(line: 67, column: 1, scope: !40)
!48 = !DILocation(line: 69, column: 1, scope: !40)
!49 = !DILocation(line: 71, column: 1, scope: !40)
!50 = !DILocation(line: 74, column: 1, scope: !40)
!51 = !DILocation(line: 75, column: 1, scope: !40)
!52 = !DILocation(line: 77, column: 1, scope: !40)
!53 = !DILocation(line: 78, column: 1, scope: !40)
!54 = !DILocation(line: 79, column: 1, scope: !40)
!55 = !DILocation(line: 81, column: 1, scope: !40)
!56 = !DILocation(line: 83, column: 1, scope: !40)
!57 = !DILocation(line: 85, column: 1, scope: !40)
!58 = !DILocation(line: 86, column: 1, scope: !40)
