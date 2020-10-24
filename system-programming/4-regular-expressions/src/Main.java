import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;
import java.util.regex.Pattern;

public class Main {

    private final static String str = "[a-zA-Z_][a-zA-Z_0-9]*";
    private final static String num10 = "[-]?[0-9]+[uUlL]?";
    private final static String numR = "[-]?[0-9]+[.][0-9]*";
    private final static String num8 = "[-]?[0][0-7]+";
    private final static String num16 = "[-]?[0][xX][0-9a-fA-F]+";
    private final static String numE = "[-]?[1-9][.]?[0-9]*[eE][-]?[0-9]+";
    private final static String operators = "[#-+*/=(),.?!&`';:<>{}]{1}|[()-+?&:<>]{2}";

    public static void main(String[] args) {
        final String fileName = "in.txt";
        File file = new File(fileName);

        try {
            Scanner scanner = new Scanner(file);
            System.out.println("Reading from file...");
            try {
                FileWriter myWriter = new FileWriter("out.txt");
                Boolean isOpenComment = false;
                while (scanner.hasNextLine()) {
                    String[] data = scanner.nextLine().split(" ");
                    for (String lexem : data) {
                        if (isOpenComment)
                            continue;
                        if (lexem.isEmpty())
                            continue;
                        if (lexem.startsWith("//"))
                            break;
                        if (lexem.startsWith("/*") && !isOpenComment) {
                            isOpenComment = true;
                            continue;
                        }
                        if (lexem.endsWith("*/") && isOpenComment) {
                            isOpenComment = false;
                            continue;
                        }
                        String lexemClass = "Error";
                        if (Pattern.matches(str, lexem))
                            lexemClass = "String";
                        if (Pattern.matches(num10, lexem))
                            lexemClass = "Number constant base 10";
                        if (Pattern.matches(num8, lexem))
                            lexemClass = "Number constant base 8";
                        if (Pattern.matches(num16, lexem))
                            lexemClass = "Number constant base 16";
                        if (Pattern.matches(numR, lexem))
                            lexemClass = "Number constant float";
                        if (Pattern.matches(numE, lexem))
                            lexemClass = "Number constant ex";
                        if (Pattern.matches(operators, lexem))
                            lexemClass = "Operator";
                        myWriter.write(lexemClass + " => " + lexem + "\n");
                    }
                }
                myWriter.close();
            } catch (IOException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }
            scanner.close();
            System.out.println("Successfully wrote to the file.");
        } catch (Exception e) {
            System.out.println(e);
        }


    }
}
