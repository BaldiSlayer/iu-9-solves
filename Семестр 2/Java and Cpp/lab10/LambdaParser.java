import java.util.*;

public class LambdaParser {
    private String input;
    private int index;

    public LambdaParser(String input) {
        this.input = input;
        this.index = 0;
    }

    public void parse() {
        clean();

        ArrayList<Node> res = new ArrayList<>();

        while (index < input.length()) {
            if (input.charAt(index) == ':') {
                res.add(parseApply());
            }
            else {
                res.add(parseLambda());
            }
        }


        if (index != input.length()) {
            throw new RuntimeException("Unexpected input at position " + index);
        }

        for (Node i : res) {
            System.out.println(i.toString());
        }
    }

    private void clean() {
        while (index < input.length() && input.charAt(index) == ' ') {
            ++index;
        }
    }

    private Node parseLambda() {
        clean();

        Node result;
        if (Character.isDigit(input.charAt(index))) {
            int start = index;
            while (index < input.length() && Character.isDigit(input.charAt(index))) {
                index++;
            }
            int num = Integer.parseInt(input.substring(start, index));
            result = new Node("NUMBER", Integer.toString(num));
            result.addChild(parseApply());
        } else if (input.charAt(index) == '-') {
            index++;
            if (input.charAt(index) != '>') {
                throw new RuntimeException("Unexpected input at position " + index);
            }
            index++;
            result = new Node("->");
            Node some = parseLambda();
            result.addChild(some);
        } else if (input.charAt(index) == '(') {
            index++;
            result = parseLambda();
            if (input.charAt(index) != ')') {
                throw new RuntimeException("Unexpected input at position " + index);
            }
            index++;
        } else if (input.charAt(index) == ':') {
            result = parseApply();
        } else {
            throw new RuntimeException("Unexpected input at position " + index);
        }
        return result;
    }

    private Node parseApply() {
        clean();

        if (index < input.length() && input.charAt(index) == ':') {
            index++;
            Node result = new Node(":");
            result.addChild(parseLambda());
            result.addChild(parseApply());
            return result;
        } else {
            return new Node("ε");
        }
    }

    private static class Node {
        private String label;
        private String value;
        private List<Node> children;

        public Node(String label) {
            this.label = label;
            this.value = null;
            this.children = new ArrayList<>();
        }

        public Node(String label, String value) {
            this.label = label;
            this.value = value;
            this.children = new ArrayList<>();
        }

        public void addChild(Node child) {
            this.children.add(child);
        }

        public String toString() {
            StringBuilder sb = new StringBuilder();
            sb.append(label);
            if (value != null) {
                sb.append("(").append(value).append(")");
            }
            for (Node child : children) {
                sb.append(" ").append(child.toString());
            }
            return sb.toString();
        }
    }
}
