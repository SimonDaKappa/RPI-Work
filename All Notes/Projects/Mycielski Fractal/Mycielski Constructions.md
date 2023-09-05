Constructs a larger triangle-free graph of higher chromatic number given a triangle-free graph

### Vertices
The vertex count of a $k$-Mycielski graph is given by 
$$
|V(M_k)| = 
\left\{ \begin{array}{lr}
1 &\text{for } n = 1\\
3 \cdot 2^{n-2}-1 &\text{for } n > 1 \\
\end{array} \right\}
$$
With the given sequence $k = 1,2,\ldots$ $|V(M_k)| = 1,2,5,11,23,47,95,191,383,767$ OEIS [A083329](http://oeis.org/A083329)

#### Sequence Bound
The above vertex sequence is clearly $O(2^n)$. Giving a maximum feasible depth of [k < 20](https://sparse.tamu.edu/Mycielski?per_page=All)


### Edges
The edge count of $k$-Mycielski graph is given by
$$
|E(M_k)| = \frac{1}{2}\left(7\cdot 3^{n-2}+1 - 3\cdot2^{n-2}\right)
$$
With the given sequence $k = 1,2,\ldots$ $|E(M_k)| = 1,5,20,71,236,755,2360$ OIES [A122695](https://oeis.org/A122695)

### The first 20 Iterative Mycielskians

The first 20 (and only remotely feasible) Mycielskians can be found [here](https://sparse.tamu.edu/Mycielski?per_page=All)
Given the sparsity 

#### Sparsity Representation
One can note that mycielskians have an inherent fractal nature, as show in the following matrix sparsity images of the first 10.
2. ![[Pasted image 20230807152811.png]]
3. ![[Pasted image 20230807152825.png]]
4. ![[Pasted image 20230807152833.png]]
5. ![[Pasted image 20230807152839.png]]
6. ![[Pasted image 20230807152857.png]]
7. ![[Pasted image 20230807152903.png]]
8. ![[Pasted image 20230807152911.png]]
9. ![[Pasted image 20230807152922.png]]
10. ![[Pasted image 20230807152934.png]]

Alternatively

#### $\mathbb{R}^2$ Embedding 
Additionally, taking a look at the first four Mycielskians (excluding $M_1$ which is just a trivial single vertex no edge graph), we can see a inkling of fractality emerge. The shape of which depends on the [drawing function](obsidian://open?vault=All%20Notes&file=Projects%2FMycielski%20Fractal%2FDefinitions)
![[Pasted image 20230807153722.png]]![[Pasted image 20230807154257.png]]
