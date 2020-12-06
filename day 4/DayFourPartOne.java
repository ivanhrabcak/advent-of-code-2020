import java.io.*;
import java.util.*;
import java.util.function.*;
import java.util.stream.Collector;

public class DayFourPartOne {
    public static final String[] requiredFields = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

    public static boolean isValid(String passport) {
        Map<String, String> passportEntries = new HashMap<>();
        Arrays.stream(passport.split(" ")).forEach(new Consumer<String>() {
            @Override
            public void accept(String s) {
                String[] keyValuePair = s.split(":");
                passportEntries.put(keyValuePair[0], keyValuePair[1]);
            }
        });

        return passportEntries.keySet().containsAll(Arrays.asList(requiredFields.clone()));
    }

    public static void main(String[] args) throws IOException {
        File file = new File("input.txt");
        FileInputStream stream = new FileInputStream(file);

        List<String> input = new ArrayList<>();

        Arrays.stream(new String(stream.readAllBytes())
                .split("\n\n"))
                .forEach(s -> input.add(s.replace("\n", " ")));

        final int[] validPassports = {0};
        input.forEach(s -> {
            if (isValid(s)) validPassports[0]++;
        });

        System.out.println(validPassports[0]);


    }
}