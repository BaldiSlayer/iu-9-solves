public class Fraction implements Comparable<Fraction> {
    public int ch, zn;

    public Fraction(int ch_, int zn_) {
        this.ch = ch_;
        this.zn = zn_;
    }

    @Override
    public String toString() {
        return "Fraction {"
                + "Числитель='" + this.ch + '\''
                + ", Знаметель='" + this.zn
                + "'}";
    }

    @Override
    public int compareTo(Fraction o) {
        return (this.ch * o.zn) - (o.ch * this.zn);
    }
}