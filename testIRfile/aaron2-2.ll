; ModuleID = 'aaron2-2.bc'
source_filename = "../testCfile/aaron2-2.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@tx = common dso_local global i32 0, align 4
@x = common dso_local global i32 0, align 4
@y = common dso_local global i32 0, align 4

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  store i32 0, i32* @tx, align 4
  store i32 0, i32* @x, align 4
  store i32 0, i32* @y, align 4
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %tmp = load i32, i32* @x, align 4
  %tmp1 = load i32, i32* @y, align 4
  %cmp = icmp sge i32 %tmp, %tmp1
  br i1 %cmp, label %land.rhs, label %land.end

land.rhs:                                         ; preds = %while.cond
  %tmp2 = load i32, i32* @tx, align 4
  %cmp1 = icmp sge i32 %tmp2, 0
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %tmp3 = phi i1 [ false, %while.cond ], [ %cmp1, %land.rhs ]
  br i1 %tmp3, label %while.body, label %while.end

while.body:                                       ; preds = %land.end
  %tmp4 = load i32, i32* @y, align 4
  %add = add nsw i32 %tmp4, 1
  %tmp5 = load i32, i32* @tx, align 4
  %add2 = add nsw i32 %add, %tmp5
  store i32 %add2, i32* @y, align 4
  br label %while.cond

while.end:                                        ; preds = %land.end
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 10.0.1 "}
