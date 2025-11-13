
GPIO_TypeDef *ledPorts[4] = {GPIOA, GPIOB, GPIOB, GPIOB};
uint16_t      ledPins[4]  = {GPIO_PIN_10, GPIO_PIN_3, GPIO_PIN_10, GPIO_PIN_4};

void showCodeWord(uint8_t value);
static void MX_GPIO_Init(void);


int main(void)
{
  HAL_Init();              // inicijalizacija HAL biblioteke
  SystemClock_Config();    // init takta (generira CubeMX)
  MX_GPIO_Init();          // inicijalizacija GPIO pinova

  while (1)
  {
    // prolazi kroz sve 4-bitne vrijednosti: 0..15
    for (uint8_t value = 0; value < 16; value++)
    {
      showCodeWord(value);   // postavi LED-ice prema bitovima
      HAL_Delay(500);        // 0.5 s pauze
    }
    
  }
}


void showCodeWord(uint8_t value)
{
  for (uint8_t bit = 0; bit < 4; bit++)
  {
    uint8_t bitValue = (value >> bit) & 0x01;  // izdvoji bit

    HAL_GPIO_WritePin(
      ledPorts[bit],
      ledPins[bit],
      bitValue ? GPIO_PIN_SET : GPIO_PIN_RESET
    );
  }
}



static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // Uključi clock za GPIOA i GPIOB
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  // Postavi PA10 (D2) kao izlaz
  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  // Postavi PB3, PB4, PB10 (D3, D5, D4) kao izlaze
  GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  // Na početku sve LED-ice ugasi
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_10, GPIO_PIN_RESET);
}
