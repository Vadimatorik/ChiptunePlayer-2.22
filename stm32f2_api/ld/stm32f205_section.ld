/* Описание областей памяти МК +стек. */
/* Вершина стека (этот адрес будет размещен в таблице векторов прерываний). */
_stack = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
  /* Таблица векторов прерываний, выравниванная по 4 байта (во flash). */
  .irq_table :
  {
    . = ALIGN(4);		/* Задаем счетчику адрес кратный 4-м байтам. */
    KEEP(*(.irq_table)) 	/* Данную секцию нельзя удалять (KEEP). */	
    . = ALIGN(4);
  } >FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text)     				/* Основная программа во flash. */
    *(.rodata)					/* Неизменяемые данные во flash. */
    . = ALIGN(4);      
  } >FLASH

  /* ARM magic sections */
  /* Не ясно, для чего нужная секция, но без нее не собирается. */
  .ARM.extab :
  {
       *(.ARM.extab* .gnu.linkonce.armextab.*)
  } > FLASH
   	
  __exidx_start = .;   	
  .ARM.exidx :
  {
    *(.ARM.exidx* .gnu.linkonce.armexidx.*)
  } > FLASH
  __exidx_end = .;

  /* Изменяемые данные, в RAM (копируются из flash). */
  _sidata = ALIGN(4);		/* Получаем адрес исходных значений изменяемых данных. */

  .data : AT ( _sidata )
  {
    . = ALIGN(4);		/* Обязательно выравниваем по 4 байта. */
    _sdata = .;
    *(.data)     
    . = ALIGN(4);
    _edata = .;    
  } >RAM			/* Секция располагается в RAM, но продублирована во flash. */


  /* Данные в RAM, изначально 0 (заполняются нулями). */
  .bss (NOLOAD) :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    *(.bss)
    . = ALIGN(4);
    __bss_end__ = .;
  } >RAM
}


