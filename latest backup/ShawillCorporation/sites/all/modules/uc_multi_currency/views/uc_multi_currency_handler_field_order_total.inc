<?php

class uc_multi_currency_handler_field_order_total extends views_handler_field {

  /**
   * Constructor.
   */
  function construct() {
    parent::construct();
    $this->additional_fields['order_total'] = 'order_total';
    $this->additional_fields['currency'] = 'currency';
  }

  /**
   * Overrides views_handler_field::query().
   */
  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
    // Do nothing else with the query, we'll be retrieving the information directly.
  }

  /**
   * Overrides views_handler::option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['format'] = array('default' => 'uc_multi_currency_price');
    return $options;
  }

  /**
   * Overrides views_handler::options_form().
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $options = $this->options;

    $form['format'] =  array(
      '#title' => t('Format'),
      '#type' => 'radios',
      '#options' => array(
        'uc_multi_currency_price' => t('Ubercart multi-currency price'),
        'numeric' => t('Numeric'),
      ),
      '#default_value' => $options['format'],
      '#weight' => 1,
    );

    // Change weight and dependency of the previous field on the parent numeric ones
    $weight = 2;
    foreach (array('set_precision', 'precision', 'decimal', 'separator', 'prefix', 'suffix') as $field) {
      if (isset($form[$field]['#dependency'])) {
        $form[$field]['#dependency'] += array('radio:options[format]' => array('numeric'));
        $form[$field]['#dependency_count'] = count($form[$field]['#dependency']);
      }
      else {
        $form[$field]['#dependency'] = array('radio:options[format]' => array('numeric'));
      }

      $form[$field]['#weight'] = ++$weight;
    }
  }

  /**
   * Overrides views_handler_field::render().
   */
  function render($values) {
    $total = $values->{$this->aliases['order_total']};

    if ($this->options['format'] == 'numeric') {
      return $total;
    }

    if ($this->options['format'] == 'uc_multi_currency_price') {
      $this->field_alias = 'order_total';
      $currency = _uc_multi_currency_currency_load($values->{$this->aliases['currency']});
      return uc_multi_currency_format($total, $currency);
    }
  }

}
