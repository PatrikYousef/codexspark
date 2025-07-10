#include <iostream>
#include <vector>
#include <limits>

using namespace std;

void PressEnter() {
    cout << "\nPress Enter to continue...\n";
    cin.get();
}

void clearScreen(){
    #ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

}

void FindingRightPerson() {
    vector<string> rightperson{
        "💡 Attraction is a spark, but godly character is the foundation.",
        "❤️ Look for someone who shares your faith and values (2 Corinthians 6:14).",
        "🧠 Consider: Do they lead you closer to Christ or further away?",
        "🔍 Don't just ask 'Do I like them?' — ask 'Would they be a good spouse, parent, and partner for life?'",
        "🙏 Trust God’s timing. Rushing can lead to regret.",
        "🔎 Observe their relationships with family and friends.",
        "📅 Spend time in different situations to see true character.",
        "💬 Honest communication about your expectations is vital early on."
    };
    for (const string& line : rightperson) {
         clearScreen();
        cout << line << endl;
        PressEnter();
    }
}

void EmotionalMaturity() {
    vector<string> emotionalmaturity {
        "🧠 Emotionally mature people take responsibility for their actions.",
        "🛑 They can say 'I'm sorry' and mean it.",
        "🫀 They're not driven by jealousy, insecurity, or control.",
        "🗣️ They communicate openly instead of shutting down or exploding.",
        "📖 'A fool gives full vent to his spirit, but a wise man quietly holds it back.' — Proverbs 29:11",
        "🌱 They understand personal growth is a lifelong process.",
        "🤝 They respect your feelings and are willing to compromise.",
        "🧘 They manage stress without taking it out on you."
    };
    for (const string& line : emotionalmaturity) {
         clearScreen();
        cout << line << endl;
        PressEnter();
    }
}

void GodlyCommunication() {
    vector<string> facts{
        "👂 Listen more than you speak (James 1:19).",
        "🗨️ Speak truth in love — not sarcasm, guilt, or manipulation.",
        "🙌 Communication is more about understanding than winning.",
        "🙏 Pray before discussing difficult topics.",
        "❤️ Kind, honest words build trust over time.",
        "🕊️ Be quick to forgive when misunderstandings happen.",
        "📵 Avoid arguing when tired or angry — wait until calmer.",
        "🤔 Ask questions to understand, don't assume or judge."
    };
    for (const string& line : facts) {
         clearScreen();
        cout << line << endl;
        PressEnter();
    }
}

void RedFlags() {
    vector<string> redflag{
        "🚩 They constantly disrespect you or others.",
        "🚩 They mock your faith or make you feel guilty for loving Jesus.",
        "🚩 They avoid accountability and resist wise counsel.",
        "🚩 Their words and actions don’t match.",
        "🚩 You feel anxious, confused, or emotionally exhausted around them.",
        "🚩 They pressure you to move faster than you’re comfortable with.",
        "🚩 They refuse to apologize or admit mistakes.",
        "🚩 You feel unsafe physically, emotionally, or spiritually."
    };
    for (const string& line : redflag) {
         clearScreen();
        cout << line << endl;
        PressEnter();
    }
}

void LoveVsInfatuation() {
    vector<string> lovevsinfatuation = {
        "💞 Infatuation fades — real love grows deeper over time.",
        "🔥 Infatuation is intense and fast; love is steady and patient.",
        "🎭 Infatuation overlooks flaws; love sees them and still chooses to stay (1 Corinthians 13).",
        "🧩 Real love involves choice, not just feelings.",
        "🕊️ 'Love is patient, love is kind... it does not boast, it is not proud.' — 1 Corinthians 13:4-7",
        "⌛ Real love waits and perseveres through difficulties.",
        "🎯 Love supports each other's growth rather than demands change.",
        "💡 Love is about giving, not just receiving."
    };
    for (const string& line : lovevsinfatuation) {
         clearScreen();
        cout << line << endl;
        PressEnter();
    }
}

void GrowTogether() {
    vector<string> lovetogether{
        "📖 Study the Word together — start small and be consistent.",
        "🙏 Pray for and with one another regularly.",
        "⛪ Serve in ministry or outreach as a team.",
        "🧠 Encourage spiritual growth individually and as a couple.",
        "👥 Surround yourselves with godly friends and mentors.",
        "💬 Share your spiritual struggles and victories openly.",
        "📅 Set spiritual goals and check progress regularly.",
        "🎉 Celebrate answered prayers and milestones together."
    };
    for (const string& line : lovetogether) {
           clearScreen();
        cout << line << endl;
        PressEnter();
    }
}

void PreparingMarriage() {
    vector<string> preparingmarriage{
        "💬 Talk about finances, children, goals, and family values early.",
        "🛠️ Go through premarital counseling with a pastor or mentor.",
        "🧠 Learn each other’s communication styles and love languages.",
        "⛪ Understand that marriage is a covenant, not a contract.",
        "💍 'Husbands, love your wives just as Christ loved the church.' — Ephesians 5:25",
        "🎯 Discuss roles and responsibilities honestly to avoid surprises.",
        "🔍 Learn conflict resolution strategies and practice them.",
        "🌱 Commit to growing together in faith, love, and understanding."
    };
    for (const auto& line : preparingmarriage) {
        cout << line << endl;
        PressEnter();
    }
}

void HandlingConflict() {
    vector<string> conflictAdvice {
        "🗣️ Communicate openly and listen carefully — Ephesians 4:29.",
        "🙏 Pray for wisdom and patience before addressing issues.",
        "💡 Remember, you’re on the same team, not opponents.",
        "🔄 Be willing to admit mistakes and ask for forgiveness.",
        "🤝 Seek reconciliation quickly to prevent bitterness.",
        "📖 'Be kind and compassionate to one another, forgiving each other.' — Ephesians 4:32",
        "🕊️ Avoid harsh words or holding grudges.",
        "👂 Give your partner grace and listen without interrupting."
    };
    for (const auto& line : conflictAdvice) {
        cout << line << endl;
        PressEnter();
    }
}

void PrintHeader() {
    const int width = 55;
    string title = "💖 Relationship Advice Menu 💖";
    int padding = (width - (int)title.size()) / 2;

    cout << string(width + 2, '=') << "\n";
    cout << "|" << string(padding, ' ') << title << string(width - padding - title.size(), ' ') << "|\n";
    cout << string(width + 2, '=') << "\n\n";
}


int main() {
    int choice;

    while (true) {
        clearScreen();
        PrintHeader();

        cout << "==============================================\n";
        cout << "\n1. 🔍  Finding the Right Person\n";
        cout << "\n2. 🧠  Emotional Maturity\n";
        cout << "\n3. 🕊️   Godly Communication\n";
        cout << "\n4. 🚩  Red Flags\n";
        cout << "\n5. ❤️‍🔥 Real Love vs. Infatuation\n";
        cout << "\n6. 🌱  Growing Together Spiritually\n";
        cout << "\n7. 💒  Preparing for Marriage\n";
        cout << "\n8. ✌️   Handling Conflict Biblically\n";
        cout << "\n0. ❌  Exit\n";
        cout << "\n==============================================\n";

        cout << "✨ Select an option from (0 to 8): ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear input buffer

        if (choice == 0) {
            cout << "\n🙏 Thank you for using Relationship Advice. God bless! ✨\n";
            break;  // Exit the loop and program
        }  

        switch (choice) {
            case 1: FindingRightPerson(); break;
            case 2: EmotionalMaturity(); break;
            case 3: GodlyCommunication(); break;
            case 4: RedFlags(); break;
            case 5: LoveVsInfatuation(); break;
            case 6: GrowTogether(); break;
            case 7: PreparingMarriage(); break;
            case 8: HandlingConflict(); break;
            default:
                cout << "\n⚠️ Invalid choice. Please try again.\n\n";
                PressEnter();
                continue;  // Go back to menu without pausing again
        }

        PressEnter();  // Wait for user before returning to menu
    }

    return 0;
}
