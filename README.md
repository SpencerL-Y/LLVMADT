# LLVMADT

# Collarborators
- Xie Li
- Weizhi Feng
- Yong Li
- Jiaxiang Liu

# WorkLog

## Xie Li
- Gap of Automaton and gwt
- Gap of Automaton and CFA  
    (DONE)
- Gap of gwt and LTLf 
- Path checker for simple LTLf
    (DONE)
- Recursive parser of LTLf
- Algorithm: sampler model checker
- Algorithm: symbolic model checker

# 开发日志

# 10月14日

## Clexma
- 实现了模块 CheckerSampleBased, 发现问题验证的时候出现了spot会将LTL公式 $\mathbf{G} x>0$中的$x>0$当作一个原子命题，这样就不能从LTL公式中得到$x > 0$这样的Z3表达式了，解决的办法：添加一个map，将$a$和$x > 0$map起来，然后写公式的时候写$\mathbf{G}a$, 生成Z3表达式的时候就可以map回来。

## Fengwz
- 在 Translator 中添加了SSA变量下标的翻译，添加了一个Map来记录路径上出现的同一个变量的次数，从而生成有意义的Z3表达式。

## 发现但尚未解决的问题

- 目前的验证只能对线性程序，因为我们的cfa上的边村的是z3表达式，应该保留从ir中获得的更多信息，因此应该存llvmapi中的instruction，在sample path的时候再生成
z3表达式。问题的核心：语法和语义。。
