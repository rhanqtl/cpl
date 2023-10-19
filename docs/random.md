# Internals of the Constraint Solver

## Solving Order

```text
class A {
    randvar xs: [i32];

    constraint cst_1 {
        0 < $len(xs) && $len(xs) <= 10;
        foreach (xs[i]) {
            if (i > 0) {
                xs[i-1] < xs[i];
            }
        }
    }
}
```

* Stage #1: solve `$len(xs)`
* Stage #2: expand the `foreach`, assume that `$len(xs) == 4`, the `foreach` is expanded to:

```text
xs[0] < xs[1];
xs[1] < xs[2];
xs[2] < xs[3];
```
