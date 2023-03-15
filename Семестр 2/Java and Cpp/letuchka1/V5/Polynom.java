import static java.lang.Math.*;
public class Polynom {
    int n;
    Point points[];
    public Polynom() {
        // по умолчанию количество вершин - одна, и одна располагается в начале координат, точке (0,0)
        this.n = 1;
        Point pt1 = new Point(0, 0);
        Point[] points = { pt1 };
        this.points = points;
    }
    
    public void Change(int n_, Point pts[]) {
        this.points = pts;
        this.n = n_;
    }
    
    public void getInfo() {
        System.out.print("points count: ");
        System.out.println(this.n);
        System.out.println("Info about points");
        for (int i = 0; i < this.n; ++i) {
            System.out.print(this.points[i].x);
            System.out.print(" ");
            System.out.print(this.points[i].y);
            System.out.print("\n");
        }
    }
}
