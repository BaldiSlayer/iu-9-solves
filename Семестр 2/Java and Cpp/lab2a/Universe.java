import java.util.ArrayList;

public class Universe {
    ArrayList<Particle> particles;
    public Universe() {
        this.particles = new ArrayList<Particle>();
    }

    public int count() {
        return this.particles.size();
    }

    public void add(Particle p) {
        this.particles.add(p);
    }

    public Point get_r_vector() {
        double sum_x = 0, sum_y = 0;

        for (Particle part : particles) {
            sum_x += part.x;
            sum_y += part.y;
        }

        Point ans = new Point(sum_x / particles.size(), sum_y / particles.size());
        return ans;
    }
}