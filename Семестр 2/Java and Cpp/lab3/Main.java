public class Main {
    public static void main(String[] args) {
        Universe u = new Universe();

        Particle a = new Particle(0, 0);
        Particle b = new Particle(2, 2);
        Particle c = new Particle(0, 2);
        Particle d = new Particle(2, 0);
        u.add(a);
        u.add(b);
        u.add(c);
        u.add(d);

        Point ans = u.get_r_vector();
        System.out.println(u.count());

        System.out.print(ans.x);
        System.out.print(" ");
        System.out.print(ans.y);
    }
}