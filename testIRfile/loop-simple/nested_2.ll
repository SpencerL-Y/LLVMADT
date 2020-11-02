; ModuleID = 'nested_2.bc'
source_filename = "../testCfile/loop-simple/nested_2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [2 x i8] c"0\00", align 1
@.str.1 = private unnamed_addr constant [11 x i8] c"nested_2.c\00", align 1
@.str.2 = private unnamed_addr constant [12 x i8] c"reach_error\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @reach_error() #0 {
entry:
  call void @__assert_fail(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i64 0, i64 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.1, i64 0, i64 0), i32 13, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.2, i64 0, i64 0)) #2
  unreachable
}

; Function Attrs: noreturn nounwind
declare dso_local void @__assert_fail(i8*, i8*, i32, i8*) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 6, i32* %a, align 4
  store i32 6, i32* %b, align 4
  store i32 0, i32* %a, align 4
  br label %for.cond

for.cond:                                         ; preds = %for.inc4, %entry
  %tmp = load i32, i32* %a, align 4
  %cmp = icmp slt i32 %tmp, 6
  br i1 %cmp, label %for.body, label %for.end6

for.body:                                         ; preds = %for.cond
  store i32 0, i32* %b, align 4
  br label %for.cond1

for.cond1:                                        ; preds = %for.inc, %for.body
  %tmp1 = load i32, i32* %b, align 4
  %cmp2 = icmp slt i32 %tmp1, 6
  br i1 %cmp2, label %for.body3, label %for.end

for.body3:                                        ; preds = %for.cond1
  br label %for.inc

for.inc:                                          ; preds = %for.body3
  %tmp2 = load i32, i32* %b, align 4
  %inc = add nsw i32 %tmp2, 1
  store i32 %inc, i32* %b, align 4
  br label %for.cond1

for.end:                                          ; preds = %for.cond1
  br label %for.inc4

for.inc4:                                         ; preds = %for.end
  %tmp3 = load i32, i32* %a, align 4
  %inc5 = add nsw i32 %tmp3, 1
  store i32 %inc5, i32* %a, align 4
  br label %for.cond

for.end6:                                         ; preds = %for.cond
  %tmp4 = load i32, i32* %a, align 4
  %cmp7 = icmp eq i32 %tmp4, 6
  br i1 %cmp7, label %land.lhs.true, label %if.then

land.lhs.true:                                    ; preds = %for.end6
  %tmp5 = load i32, i32* %b, align 4
  %cmp8 = icmp eq i32 %tmp5, 6
  br i1 %cmp8, label %if.end, label %if.then

if.then:                                          ; preds = %land.lhs.true, %for.end6
  call void @reach_error()
  br label %if.end

if.end:                                           ; preds = %if.then, %land.lhs.true
  ret i32 1
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noreturn nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { noreturn nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.1 "}
