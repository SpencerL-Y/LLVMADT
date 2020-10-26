; ModuleID = 'Parallel.bc'
source_filename = "../testCfile/Parallel.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@x = common dso_local global i32 0, align 4
@y = common dso_local global i32 0, align 4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 0, i32* @x, align 4
  store i32 0, i32* @y, align 4
  br label %while.cond

while.cond:                                       ; preds = %if.end, %entry
  %tmp = load i32, i32* @x, align 4
  %cmp = icmp sge i32 %tmp, 0
  br i1 %cmp, label %lor.end, label %lor.rhs

lor.rhs:                                          ; preds = %while.cond
  %tmp1 = load i32, i32* @y, align 4
  %cmp1 = icmp sge i32 %tmp1, 0
  br label %lor.end

lor.end:                                          ; preds = %lor.rhs, %while.cond
  %tmp2 = phi i1 [ true, %while.cond ], [ %cmp1, %lor.rhs ]
  br i1 %tmp2, label %while.body, label %while.end

while.body:                                       ; preds = %lor.end
  %tmp3 = load i32, i32* @x, align 4
  %cmp2 = icmp sge i32 %tmp3, 0
  br i1 %cmp2, label %if.then, label %if.else

if.then:                                          ; preds = %while.body
  %tmp4 = load i32, i32* @x, align 4
  %sub = sub nsw i32 %tmp4, 1
  store i32 %sub, i32* @x, align 4
  br label %if.end

if.else:                                          ; preds = %while.body
  %tmp5 = load i32, i32* @y, align 4
  %sub3 = sub nsw i32 %tmp5, 1
  store i32 %sub3, i32* @y, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br label %while.cond

while.end:                                        ; preds = %lor.end
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.1 "}
