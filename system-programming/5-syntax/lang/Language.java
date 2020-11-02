package lang;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;

public class Language {
    private char axioma = 'S';
    private String epsilon ="e";
    private boolean create;
    private static HashMap<Character, ArrayList<String>> rules = new HashMap<>();
    private static ArrayList<Character> terminals = new ArrayList<>();
    private static ArrayList<Character> nonterminals = new ArrayList<>();
    private static  ArrayList<Character> epsilonNonterminals = new ArrayList<>();

    public Language(String fileName) {
        File file = new File(fileName);
        String[] line;
        try {
            Scanner scanner = new Scanner(file);
            System.out.println("Reading from file...");
            line = scanner.nextLine().split(" ");
            axioma = line[0].charAt(0);
            epsilon = line[1].substring(0, 1);
            createNonterminals(scanner);
            createTerminals(scanner);
            createRules(scanner);
        } catch (Exception e) {
            System.out.println("GGGG" + e);
        }
        create = true;
    }

    public boolean isCreate() {
        return create;
    }

    public void printTerminals() {
        System.out.println("Terminals:");
        for (Character t : terminals) {
            System.out.print(t + "_");
        }
        System.out.println();
    }

    public void printNonterminals() {
        System.out.println("Non-terminals:");
        for (Character nt : nonterminals) {
            System.out.print(nt + "_");
        }
        System.out.println();
    }

    public ArrayList<Character> createLeftRecursNonterminal() {
        ArrayList<Character> left = new ArrayList<>();
        for (Character nt : nonterminals) {
            if (isLeftRecursNonterminal(nt)) {
                left.add(nt);
            }
        }
        return left;
    }

    public Boolean isLeftRecursNonterminal(Character nt) {
        HashSet<Character> s = new HashSet<>();
        int v = -1;
        if (rules.get(nt) == null) {
            return false;
        }
        for (String rule : rules.get(nt)) {
            int i = 0;
            while (i < rule.length() && epsilonNonterminals.contains(rule.charAt(i))) {
                s.add(rule.charAt(i));
                i++;
            }
            if (i < rule.length() && nonterminals.contains(rule.charAt(i))) {
                s.add(rule.charAt(i));
            }
        }
        while (s.size() != v) {
            v = s.size();
            HashSet<Character> addS = new HashSet<>();
            for (Character ch : s) {
                if (rules.get(ch) == null) {
                    break;
                }
                for (String rule : rules.get(ch)) {
                    int i = 0;
                    while (i < rule.length() && epsilonNonterminals.contains(rule.charAt(i))) {
                        addS.add(rule.charAt(i));
                        i++;
                    }
                    if (i < rule.length() && nonterminals.contains(rule.charAt(i))) {
                        addS.add(rule.charAt(i));
                    }
                }
            }
            s.addAll(addS);
        }
        return s.contains(nt);
    }

    public ArrayList<Character> getTerminals() {
        return terminals;
    }

    public ArrayList<Character> getNonTerminals() {
        return nonterminals;
    }

    public ArrayList<Character> getEpsilonNonterminals() {
        return epsilonNonterminals;
    }

    public void printEpsilonNonterminals() {
        System.out.println("Epsilon non-terminals:");
        for (Character nt : epsilonNonterminals) {
            System.out.print(nt + "_");
        }
        System.out.println();
    }

    public void setEpsilonNonterminals(ArrayList<Character> eps) {
        epsilonNonterminals = eps;
    }

    public ArrayList<Character> createEpsilonNonterminals() {
        ArrayList<Character> epsNt = new ArrayList<>();
        rules.forEach((key,val) -> {
            for (String ch : val) {
                if (ch.equals(epsilon)) {
                    epsNt.add(key);
                    break;
                }
            }
        });
        int v = -1;
        while (epsNt.size() != v) {
            v = epsNt.size();
            ArrayList<Character> newEps = new ArrayList<>();
            rules.forEach((key,val) -> {
                Boolean notEpsRule = false;
                //System.out.println(key +" " + val);
                for (String rule : val) {
                    notEpsRule = false;
                    for (int i = 0; i < rule.length(); i++) {
                        if (!epsNt.contains(rule.charAt(i))) {
                            notEpsRule = true;
                        }
                    }
                    if (!notEpsRule && !newEps.contains(key)) {
                        newEps.add(key);
                    }
                }

            });

            newEps.removeAll(epsNt);
            //System.out.println("new " + newEps);
            epsNt.addAll(newEps);

        }
        return epsNt;
    }

    private void createTerminals(Scanner scanner) {
        String[] line = scanner.nextLine().split(" ");
        for (String s : line) {
            if (!terminals.contains(s.charAt(0)))
                terminals.add(s.charAt(0));
        }
        System.out.println("Terminals created");
    }

    private void createNonterminals(Scanner scanner) {
        String[] line = scanner.nextLine().split(" ");
        nonterminals.add(axioma);
        for (String s : line) {
            if (!nonterminals.contains(s.charAt(0)))
                nonterminals.add(s.charAt(0));
        }
        System.out.println("Non-terminals created");
    }

    private void createRules(Scanner scanner) {
        String[] line;
        while (scanner.hasNextLine()) {
            line = scanner.nextLine().split(" ");
            ArrayList<String> rule = new ArrayList<>();
            for (int i = 1; i < line.length; i++) {
                for (int j = 0; j < line[i].length(); j++) {
                    if (!nonterminals.contains(line[i].charAt(j)) && !terminals.contains(line[i].charAt(j))) {
                        break;
                    }
                }
                if (!line[i].isEmpty())
                    rule.add(line[i]);
            }
            if (nonterminals.contains(line[0].charAt(0)) && !rule.isEmpty())
                rules.put(line[0].charAt(0), rule);
        }
        System.out.println("Rules created");
    }

    public int getAxioma() {
        return axioma;
    }
}
