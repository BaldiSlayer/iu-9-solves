public class Main {
    public static void main(String[] args) {
        // String input = "(-> -> 1): (-> 0: 0)";
        String input = "(-> -> 1)";
        LambdaParser parser = new LambdaParser(input);
        parser.parse();

    }
}