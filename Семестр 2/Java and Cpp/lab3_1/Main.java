import java.util.Arrays;

public class Main {
    public static void main (String[] args){
        Num[] nums = new Num[]{
                new Num(10),
                new Num(12),
                new Num(7),
                new Num(21),
        };
        Arrays.sort(nums);
        for (Num num: nums) {
            System.out.println(num);
        }
    }
}