public class Line {
    double x1, x2, y1, y2;
    double k;
    double b;
    Line(Point a, Point b) {
        this.x1 = a.x; this.x2 = b.x;
        this.y1 = a.y; this.y2 = b.y;
        this.k = (b.y - a.y) / (b.x - a.x);
        this.b = (-x1 * y2 + y1*x2) / (x2 - x1);
    }

    Line(double a, double b, double c, double d) {
        this.x1 = a; this.x2 = c;
        this.y1 = b; this.y2 = d;
        this.k = (d - b) / (c - a);
        this.b = (-x1 * y2 + y1*x2) / (x2 - x1);
    }

    double find(double x) {
        return (y2*x - y1*x - x1*y2 + y1*x2) / (x2 - x1);
    }

    Point intersect(Line second) {
        double x = (second.b - this.b) / (this.k - second.k);
        double y = find(x);
        return new Point(x, y);
    }
}