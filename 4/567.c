bool checkInclusion(char *s1, char *s2)
{
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    if (len1 > len2) {
        return false;
    }

    int count1[26] = {0};
    int count2[26] = {0};

    for (int i = 0; i < len1; i++) {
        count1[s1[i] - 'a']++;
    }

    for (int i = 0; i < len1; i++) {
        count2[s2[i] - 'a']++;
    }

    bool match = true;
    for (int i = 0; i < 26; i++) {
        if (count1[i] != count2[i]) {
            match = false;
            break;
        }
    }
    if (match) {
        return true;
    }

    for (int i = len1; i < len2; i++) {
        count2[s2[i - len1] - 'a']--;
        count2[s2[i] - 'a']++;
        match = true;
        for (int j = 0; j < 26; j++) {
            if (count1[j] != count2[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            return true;
        }
    }
    
    return false;
}
