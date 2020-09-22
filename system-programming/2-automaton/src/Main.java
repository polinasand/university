import javax.print.DocFlavor;
import java.io.File;
import java.util.*;

public class Main {

    // create automaton
    private static HashMap<Integer, HashMap<Character, Integer>> automaton = new HashMap<>();
    private static Boolean [] used = new Boolean[0];
    private static HashSet<Character> alphabet = new HashSet<>();
    private static HashSet<Integer> finalStates = new HashSet<>();
    private static String word;

    public static void main(String[] args) {

	    // init input file
        final String fileName = "in1.txt";
        File file = new File(fileName);
        try {
            Scanner scanner = new Scanner(file);
            System.out.println("Reading from file...");
            System.out.println("Reading word...");
            word = scanner.nextLine();
            int alphabetSize = Integer.parseInt(scanner.nextLine());
            for (int i = 0; i <= alphabetSize; i++) {
                alphabet.add((char)('a' + i));
            }

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
                System.out.println(sf + " " + ch + " " + st);
                try {
                    HashMap<Character, Integer> hm = new HashMap<>();
                    if (automaton.get(sf) != null){
                        hm = automaton.get(sf);
                    }
                    hm.put(ch, st);
                    automaton.put(sf, hm);
                } catch (IndexOutOfBoundsException e) {
                    System.out.println(e);
                }
            }

            //word = "dd";
            System.out.println("Automaton: " + automaton);
            System.out.println("Word w0 = " + word);

            // create set of states, that can be reached from s0
            System.out.println("Create start states");
            HashSet<Integer> startStates = new HashSet<>();
            used = new Boolean[statesSize];
            Arrays.fill(used, false);
            dfs(startStates, s0);
            System.out.println(startStates);

            // create set of states, that can be reached from final states
            System.out.println("Create finish states");
            HashSet<Integer> finishStates = new HashSet<>();
            for (int state = 0; state < statesSize; state++) {
                HashSet<Integer> states = new HashSet<>();
                used = new Boolean[statesSize];
                Arrays.fill(used, false);
                dfs(states, state);
                for (Integer finalState : finalStates) {
                    if (states.contains(finalState)) {
                        finishStates.add(state);
                        break;
                    }
                }
            }
            System.out.println(finishStates);

            // Check if w0 contains between w1 and w2
            System.out.println("Check for w0...");
            for (Integer state : startStates) {
                used = new Boolean[statesSize];
                Arrays.fill(used, false);
                if (pathExists(state, finishStates)) {
                    out("Correct word.");
                    return;
                }
            }
            out("Incorrect word.");

        } catch (Exception exception) {
            System.out.println(exception);
        }


    }

    private static void dfs(HashSet<Integer> states, int state) {
        used[state] = true;
        states.add(state);
        HashMap<Character, Integer> map = automaton.get(state);
        if (map == null) {
            return;
        }
        for (Map.Entry<Character, Integer> entry : map.entrySet()) {
            if (alphabet.contains(entry.getKey()) && !used[entry.getValue()]) {
                dfs(states, entry.getValue());
            }
        }
        return;
    }

    private static Boolean pathExists(int state, HashSet<Integer> states) {
        int currState = state;
        for (char letter : word.toCharArray()) {
            int nextState = 0;
            if (automaton.get(currState) != null) {
                if (automaton.get(currState).get(letter) != null) {
                    nextState = automaton.get(currState).get(letter);
                    currState = nextState;
                } else {
                    return false;
                }
            } else {
                return false;
            }
        }
        if (states.contains(currState) && currState != state) {
            return true;
        }
        return false;
     }

     private static void out(String message) {
        System.out.println(message);
     }
}
