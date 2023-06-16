namespace Solution {
    open Microsoft.Quantum.Primitive;
    open Microsoft.Quantum.Canon;

    operation Solve (x : Qubit[], y : Qubit) : Unit {
        body (...) {
            for (i in 0..Length(x) - 1) {
                X(x[i]);
            }
            
            Controlled X(x, y);
            X(y);
            
            for (i in 0..Length(x) - 1) {
                X(x[i]);
            }
        }
        adjoint auto;
    }
}