## Dijkstra's Algorithm

**Date**: 24th-sept-2020, Week 3 Assignment
___

### Summary:

Creates a random graph. Selects the first node and then iterates through the
rest of the nodes counting the number of connected paths using Dijkstra
algorithm and summing there scores. Finally outputs the average size of path.

### Setup:

To compile and run program:

```sh
make all
```

To compile and run tests:

```sh
make tests
```

### Examples:

Edge values in 1.0 to 10.0 and connection probability 0.2:

```
Total connected nodes to first node:	50
Average size of path:			       3.44
```

Edge values in 1.0 to 10.0 and connection probability 0.4:

```
Total connected nodes to first node:	50
Average size of path:			       3.06
```
