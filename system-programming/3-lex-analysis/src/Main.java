import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.security.cert.LDAPCertStoreParameters;
import java.util.*;
import static java.lang.Math.min;

public class Main {

    private static HashMap<Integer, HashMap<Character, Integer>> automaton = new HashMap<>();
    private static final HashSet<Integer> finalStates = new HashSet<>();
    private static final HashSet<Character> alphabet = new HashSet<>();
    private static final HashSet<Character> decimal = new HashSet<>();
    private static final HashSet<Character> octal = new HashSet<>();
    private static final HashSet<Character> hexadecimal = new HashSet<>();
    private static final HashMap<Integer, String> lexicalClasses = new HashMap<>();
    private static final HashSet<String> operators = new HashSet<>();
    private static final HashSet<String> keywords = new HashSet<>();
    private static final HashSet<String> dirs = new HashSet<>();
    private static String word;
    private static int alphabetSize = 26;

    public static void main(String[] args) {

        // init
        initAlphabets();
        initStatesFile();
        initAutomaton();
        initLexicalClasses();

        // read from file
        final String fileName = "in_text.txt";
        File file = new File(fileName);
        try {
            Scanner scanner = new Scanner(file);
            System.out.println("Reading from file...");
            try {
                FileWriter myWriter = new FileWriter("out.txt");
                myWriter.write("Result:\n");
                Boolean isComment = false;
                while (scanner.hasNext()) {
                    //ArrayList<String> words = new ArrayList<>(Arrays.asList(scanner.nextLine().split(" ")));
                    String word = scanner.next();
                    if (word.startsWith("/*") && !isComment) {
                        isComment = true;
                        while (isComment) {
                            if (word.endsWith("*/")) {
                                isComment = false;
                                break;
                            }
                            word = scanner.next();
                        }
                    } else if (word.startsWith("//") && !isComment) {
                        word = scanner.nextLine();
                    } else {
                        String lexicalClass = "";
                        int state = -1;
                        if (word.startsWith("#")) {
                            String newWord = word.replaceAll("#", "");
                            if (dirs.contains(newWord)) {
                                newWord = scanner.nextLine();
                                word = word + newWord;
                                lexicalClass = "directive";

                            } else {
                                lexicalClass = "error";
                            }
                        } else if (operators.contains(word)) {
                            lexicalClass = "operator";
                        } else if (keywords.contains(word)) {
                            lexicalClass = "keyword";
                        } else {
                            state = automat(word);
                            //System.out.println(state);
                            if (finalStates.contains(state)) {
                                // System.out.println("\u001B[31m" + "Success!" + "\u001B[0m");
                                // set color
                                lexicalClass = lexicalClasses.get(state);
                            } else {
                                //System.out.println("Not success...");
                                // set red color
                                lexicalClass = "Error";
                            }
                        }
                        myWriter.write("<" + word + "> <" + lexicalClass + ">\n");
                    }
                }
                myWriter.close();

            } catch (IOException e) {
                System.out.println("An error occurred.");
                e.printStackTrace();
            }
        } catch (Exception exception) {
            System.out.println(exception);
        }
    }

    private static void initAlphabets() {
        alphabet.add('_');
        for (int i = 0; i < alphabetSize; i++) {
            alphabet.add((char)('a' + i));
            alphabet.add((char)('A' + i));
        }
        for (int i = 0; i < 10; i++) {
            decimal.add((char)('0'+i));
            hexadecimal.add((char)('0'+i));
            octal.add((char) min('0'+i, '7'));
        }
        hexadecimal.addAll(Arrays.asList('a', 'b', 'c', 'd', 'e', 'f',
                'A', 'B', 'C', 'D', 'E', 'F'));
        operators.addAll(Arrays.asList("+", "-", "=", "/", "%", "^", "|", "&", "?", "!", ",", ";",
                "(", ")", "[", "]", "{", "}", ".", ">", "<", "*", "'", "\"",
                "::", "++", "--", "->", ">>", "<<", "<=", ">=", "==", "!=", "&&", "||",
                "+=", "-=", "/=", "*=", "%=", "<<=", ">>="));
        File file = new File("in_keywords.txt");
        try {
            Scanner scanner = new Scanner(file);
            while (scanner.hasNext()) {
                keywords.add(scanner.next());
            }
        } catch (Exception e) {
            System.out.println(e);
        }

        dirs.addAll(Arrays.asList("include", "define", "ifdef", "ifndef", "endif"));
    }

    private static void initAutomaton() {
        final String fileName = "in_states.txt";
        File file = new File(fileName);
        try {
            Scanner scanner = new Scanner(file);
            int statesSize = scanner.nextInt();
            int s0 = scanner.nextInt();
            int finalStatesSize = scanner.nextInt();
            for (int i = 0; i < finalStatesSize; i++) {
                finalStates.add(scanner.nextInt());
            }

            // init automaton
            System.out.println("Init automaton states...");
            while (scanner.hasNextInt()) {
                int sf = scanner.nextInt();
                char ch = scanner.next().charAt(0);
                int st = scanner.nextInt();
                try {
                    HashMap<Character, Integer> hm = new HashMap<>();
                    if (automaton.get(sf) != null) {
                        hm = automaton.get(sf);
                    }
                    hm.put(ch, st);
                    automaton.put(sf, hm);
                } catch (IndexOutOfBoundsException e) {
                    System.out.println(e);
                }
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    private static void initStatesFile() {
        try {
            FileWriter myWriter = new FileWriter("in_states.txt");
            // number of states
            myWriter.write("23\n");
            // start state
            myWriter.write("0\n");
            // number of final states
            int finalStatesNum = 19;
            myWriter.write(finalStatesNum + "\n");
            // final states
            String fs = "1 2 3 4 10 11 12 13 16 20 21 22 23 24 26 27 28 29 30";
            myWriter.write(fs+"\n");
            // transitions
            // strings
            for (Character ch : alphabet) {
                myWriter.write("0 "+ch+" 3\n");
                myWriter.write("3 "+ch+" 3\n");
            }
            // decimal
            for (Character ch : decimal) {
                if (ch != '0') {
                    myWriter.write("0 "+ch+" 1\n");
                }
                myWriter.write("1 "+ch+" 1\n");
                // strings
                myWriter.write("3 "+ch+" 3\n");
            }
            myWriter.write("1 l 10\n");
            myWriter.write("1 L 10\n");
            myWriter.write("1 u 12\n");
            myWriter.write("1 U 12\n");
            myWriter.write("10 u 11\n");
            myWriter.write("10 U 11\n");
            myWriter.write("12 l 13\n");
            myWriter.write("12 L 13\n");

            // octal
            myWriter.write("0 0 2\n");
            for (Character ch : octal) {
                myWriter.write("2 "+ch+" 20\n");
                myWriter.write("20 "+ch+" 20\n");
            }
            myWriter.write("20 l 21\n");
            myWriter.write("20 L 21\n");
            myWriter.write("20 u 23\n");
            myWriter.write("20 U 23\n");
            myWriter.write("21 u 22\n");
            myWriter.write("21 U 22\n");
            myWriter.write("23 l 24\n");
            myWriter.write("23 L 24\n");

            //hexadecimal
            myWriter.write("2 x 25\n");
            myWriter.write("2 X 25\n");
            for (Character ch : hexadecimal) {
                myWriter.write("25 "+ch+" 26\n");
                myWriter.write("26 "+ch+" 26\n");
            }
            myWriter.write("26 l 27\n");
            myWriter.write("26 L 27\n");
            myWriter.write("26 u 29\n");
            myWriter.write("26 U 29\n");
            myWriter.write("27 u 28\n");
            myWriter.write("27 U 28\n");
            myWriter.write("29 l 30\n");
            myWriter.write("29 L 30\n");

            // exponential
            myWriter.write("1 e 14\n");
            myWriter.write("1 E 14\n");
            myWriter.write("14 - 15\n");
            for (Character ch : decimal) {
                myWriter.write("14 "+ch+" 16\n");
                myWriter.write("16 "+ch+" 16\n");
                if (ch != '0') {
                    myWriter.write("15 "+ch+" 16\n");
                }
            }

            //double
            myWriter.write("2 . 4\n");
            myWriter.write("1 . 4\n");
            for (Character ch : decimal) {
                myWriter.write("4 "+ch+" 4\n");
            }

            myWriter.close();
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    private static void initLexicalClasses() {
        lexicalClasses.put(-1, "error");
        lexicalClasses.put(1, "number constant");
        lexicalClasses.put(2, "number constant");
        lexicalClasses.put(4, "number constant");
        lexicalClasses.put(10, "number constant");
        lexicalClasses.put(11, "number constant");
        lexicalClasses.put(12, "number constant");
        lexicalClasses.put(13, "number constant");
        lexicalClasses.put(16, "number constant");
        lexicalClasses.put(20, "number constant");
        lexicalClasses.put(21, "number constant");
        lexicalClasses.put(22, "number constant");
        lexicalClasses.put(23, "number constant");
        lexicalClasses.put(24, "number constant");
        lexicalClasses.put(26, "number constant");
        lexicalClasses.put(27, "number constant");
        lexicalClasses.put(28, "number constant");
        lexicalClasses.put(29, "number constant");
        lexicalClasses.put(30, "number constant");
        lexicalClasses.put(3, "string constant");
    }

    private static int automat(String word) {
        int q = 0;
        try {
            for (int i = 0; i < word.length(); i++) {
                HashMap<Character, Integer> hm = automaton.get(q);
                if (hm != null &&  hm.get(word.charAt(i)) != null) {
                    q = hm.get(word.charAt(i));
                    //System.out.println(q);
                } else {
                    return -1;
                }
            }
        } catch (Exception e) {
            System.out.println(e);
        }
        return q;
    }

}
