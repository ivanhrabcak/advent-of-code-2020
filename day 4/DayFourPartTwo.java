import ru.lanwen.verbalregex.VerbalExpression;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.*;
import java.util.function.Consumer;

public class DayFourPartTwo {
    public static final String[] requiredFields = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"};

    public static VerbalExpression yearExpression = VerbalExpression.regex()
            .digit().count(4)
            .build();

    public static VerbalExpression heightExpression = VerbalExpression.regex()
            .digit().oneOrMore().oneOf("cm", "in")
            .build();

    public static String[] validHexCharacters = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                                                 "a", "b", "c", "d", "e", "f"};
    public static VerbalExpression hexColorExpression = VerbalExpression.regex()
            .add("#").oneOf(validHexCharacters).count(6)
            .build();

    public static String[] validHairColors = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
    public static VerbalExpression eyeColorExpression = VerbalExpression.regex()
            .oneOf(validHairColors)
            .build();

    public static VerbalExpression idExpression = VerbalExpression.regex()
            .digit().count(9)
            .build();

    public static boolean isValueBetween(int x, int y, int value) {
        return value >= x && value <= y;
    }

    public static boolean isValid(String passport) {
        Map<String, String> passportEntries = new HashMap<>();
        Arrays.stream(passport.split(" ")).forEach(s -> {
            String[] keyValuePair = s.split(":");
            passportEntries.put(keyValuePair[0], keyValuePair[1]);
        });

        return passportEntries.keySet().containsAll(Arrays.asList(requiredFields.clone()))
                && areAllFieldsValid(passportEntries);
    }

    public static boolean areAllFieldsValid(Map<String, String> passportEntries) {
        for (Map.Entry<String, String> entry : passportEntries.entrySet()) {
            switch (entry.getKey()) {
                case "byr":
                    if (!(yearExpression.testExact(entry.getValue())
                            && isValueBetween(1920, 2002, Integer.parseInt(entry.getValue())))) {
                        return false;
                    }
                    break;
                case "iyr":
                    if (!(yearExpression.testExact(entry.getValue())
                            && isValueBetween(2010, 2020, Integer.parseInt(entry.getValue())))) {
                        return false;
                    }
                    break;
                case "eyr":
                    if (!(yearExpression.testExact(entry.getValue())
                            && isValueBetween(2020, 2030, Integer.parseInt(entry.getValue())))) {
                        return false;
                    }
                    break;
                case "hgt":
                    if (!heightExpression.testExact(entry.getValue())) {
                        return false;
                    }
                    int height = Integer.parseInt(entry.getValue()
                            .replace("cm", "")
                            .replace("in", ""));

                    boolean metric = entry.getValue().contains("cm");
                    if (metric && !isValueBetween(150, 193, height)) {
                        return false;
                    }
                    else if (!metric && !isValueBetween(59, 76, height)) {
                        return false;
                    }
                    break;
                case "hcl":
                    if (!hexColorExpression.testExact(entry.getValue())) {
                        return false;
                    }
                    break;
                case "ecl":
                    if (!eyeColorExpression.testExact(entry.getValue())) {
                        return false;
                    }
                    break;
                case "pid":
                    if (!idExpression.testExact(entry.getValue())) {
                        return false;
                    }
            }

        }
        return true;
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
