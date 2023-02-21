public class Matrix {
    int n;
    Boolean Elements[][];
    public Matrix(int n_, Boolean elems[][])
    {
        this.n = n_;
        this.Elements = elems;
    }

    public void ChangeMatrix(int n_, Boolean elems[][]) {
        this.n = n_;
        this.Elements = elems;
    }

    public void Print() {
        for (int i = 0; i < n;++i) {
            for (int j = 0; j < n; ++j) {
                System.out.print(this.Elements[i][j]);
                System.out.print(" ");
            }
            System.out.print("\n");
        }
    }

    public void Add(Matrix b) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                this.Elements[i][j] = (this.Elements[i][j] || b.Elements[i][j]);
            }
        }
    }

    public void Multiply(Matrix b) {
       if (b.n != this.n) {
            System.out.println("Нельзя умножать матрицы разных размеров");
        }
        else {
           Boolean[][] res = new Boolean[this.n][this.n];

           for (int i = 0; i < this.n; ++i) {
               for (int j = 0 ; j < this.n; ++j) {
                   res[i][j] = false;
               }
           }

            for (int i = 0; i < this.n; i++) {
                for (int j = 0; j < this.n; j++) {
                    for (int k = 0; k < this.n; k++) {
                        res[i][j] = (res[i][j] || (this.Elements[i][k] && b.Elements[k][j]));
                    }
                }
            }
        }
    }
}
