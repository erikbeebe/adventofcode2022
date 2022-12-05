import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map.Entry;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class day1 {
    public static void main(String[] args) throws FileNotFoundException {
        BufferedReader br = new BufferedReader(new FileReader(new File("input1.txt")));
        String line;
    
        HashMap<Integer, Integer> hm = new HashMap<>();
        int elf = 0;
        int calories = 0;

        try {
            while ((line = br.readLine()) != null) {
                if (!line.isEmpty()) {
                    calories += Integer.parseInt(line);
                } else {
                    hm.put(elf, calories);
                    calories = 0;
                    elf += 1;
                }

            }
        } catch (IOException ex) {
        }

        Entry<Integer, Integer> entry = hm.entrySet()
          .stream()
          .max((e1, e2) -> Integer.compare(e1.getValue(), e2.getValue()))
          .get();

        System.out.println("Part 1 - key: " + entry.getKey() + " answer: " + entry.getValue());

        int sum = hm.values()
          .stream()
          .sorted((e1, e2) -> Integer.compare(e2, e1))
          .limit(3)
          .mapToInt(Integer::intValue)
          .sum();
        System.out.println("Part 1: " + sum);

        int total = hm
          .entrySet()
          .stream()
          .sorted(Collections.reverseOrder(Entry.comparingByValue()))
          .limit(3)
          .map(k -> k.getValue())
          .collect(Collectors.summingInt(Integer::intValue));

        System.out.println("Part 2 - total: " + total);


    }
}