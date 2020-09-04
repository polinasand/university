import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        String data = "";
        try {
            data = readFileAsString("in.txt");
            System.out.println("Reading from file...");
        } catch (Exception e) {
            System.out.println(e);
        }
        data = data.replaceAll("[\n]", "");
        List<String> words = new ArrayList<>(Arrays.asList(data.split("[-+*/= (),.?!&`';:]")));
        HashSet<String> doubleConsonants = new HashSet<>(
                Arrays.asList(
                        "bb", "cc", "dd", "ff", "gg", "hh", "jj", "kk", "ll", "mm", "nn", "pp",
                        "qq", "rr", "ss", "tt", "vv", "ww", "xx", "zz"));
        List<String> result = new ArrayList<>();
        for (String word : words) {
            for (String pair : doubleConsonants) {
                if (word.contains(pair)) {
                    if (!result.contains(word)) {
                        result.add(word);
                        break;
                    }
                }
            }
        }
        System.out.println(result);
        try {
            FileWriter myWriter = new FileWriter("out.txt");
            myWriter.write("Results:\n");
            for (String word : result) {
                if (!word.isEmpty()) {
                    myWriter.write(word + "\n");
                }
            }
            myWriter.close();
            System.out.println("Successfully wrote to the file.");
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    public static String readFileAsString(String fileName) throws Exception {
        File file = new File(fileName);
        BufferedReader reader = new BufferedReader(new FileReader(file));
        String data = "";
        String s;
        while ((s = reader.readLine()) != null) {
            data = data + " " + s;
        }
        return data;
    }
}
