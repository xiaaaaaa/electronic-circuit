//使用注意事項：現在有三段旋律(正確、錯誤、SUS)，目前是使用按鈕切換正確和錯誤的音效，SUS沒有在切換功能中
//程式能自不足只有還需要整理的功能 龜龜在此土下座orz

#define BUTTON_PIN 4    // 按鈕
#define BUZZER_PIN 12   // 蜂鳴器

bool lastButtonState = HIGH;    // 上一次按鈕狀態
bool buzzerState = false;       // 蜂鳴器狀態（是否正在播放旋律）

void playMelody(int melodyType) {
  int melodyT[] = {1047, 784, 784, 880, 784, 988, 1047};     //答對旋律(7)
  int noteDurations1[] = {4, 8, 8, 4, 2, 4, 4}; 
  int melodyF[] = {698, 1245, 1245, 1245, 1175, 1047, 932, 698, 698, 466};     //答錯旋律FD# D#D# D c A#F FA#(10)
  int noteDurations2[] = {8, 4, 8, 4, 4, 4, 8, 4, 8, 4}; 
  int melodySUS[] = {880, 1047, 1175, 1245, 1175, 1047, 880, 784, 988, 880};     //SUS旋律(10)
  int noteDurations3[] = {4, 4, 4, 4, 4, 4, 2, 8, 8, 4}; 
  int melodySize;

  // 播放旋律
  for (int thisNote = 0; thisNote < melodySize; thisNote++) {
    int noteDuration;
    int* melody;

    if (melodyType == 0) {
      melody = melodyT;
      melodySize = 7;
      noteDuration = 1000 / noteDurations1[thisNote];
    } 
    else if (melodyType == 1) {
      melody = melodyF;
      melodySize = 10;
      noteDuration = 1000 / noteDurations2[thisNote];
    }

    tone(BUZZER_PIN, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // 設置按鈕接腳為上拉輸入模式
  pinMode(BUZZER_PIN, OUTPUT); // 設置蜂鳴器接腳為輸出模式
}

void loop() {
  bool currentButtonState = digitalRead(BUTTON_PIN); // 獲取當前按鈕狀態

  // 檢測按鈕是否按下（從HIGH變為LOW表示按下）
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    // 切換旋律並播放
    buzzerState = !buzzerState;
    playMelody(buzzerState ? 1 : 0); // 根據按鈕狀態播放不同的旋律
    delay(500); // 防止按鈕彈跳
  }
  lastButtonState = currentButtonState; // 更新按鈕狀態
}
