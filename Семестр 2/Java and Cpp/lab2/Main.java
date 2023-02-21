public class Main {
    public static void main(String[] args) {
        Boolean mas1[][] = {
                {false, true},
                {true, false}
        };

        Boolean mas2[][] = {
                {true, false},
                {false, true}
        };

        Matrix m1 = new Matrix(2, mas1);
        Matrix m2 = new Matrix(2, mas2);

        m1.Add(m2);
        m1.Print();

        System.out.println("\n");

        Boolean mas3[][] = {
                {false, true},
                {true, false}
        };
        m1.ChangeMatrix(2, mas3);
        m1.Print();

        System.out.println("\n");

        m1.Multiply(m2);
        m1.Print();
    }
}