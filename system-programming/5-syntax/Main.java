import java.lang.*;
import java.util.*;
import java.io.*;
import java.nio.charset.Charset;
import lang.*;

public class Main {
    private static String fileName = "in1.txt";
    private static Language language = null;

    public static void main(String[] args) {
        if (readGrammar(fileName)) {
            ArrayList<Character> epsilon = language.createEpsilonNonterminals();
            language.setEpsilonNonterminals(epsilon);
            language.printEpsilonNonterminals();
            ArrayList<Character> leftRecNt = language.createLeftRecursNonterminal();
            System.out.println("Left recursion non-terminals:");
            for (Character nt : leftRecNt) {
                System.out.print(nt + " ");
            }
        }
    }
    public static Boolean readGrammar(String fileName) {
        language = new Language(fileName);
        if (!language.isCreate())
            return false;
        language.printNonterminals();
        language.printTerminals();
        System.out.println("Successful!");
        return true;
    }
}

