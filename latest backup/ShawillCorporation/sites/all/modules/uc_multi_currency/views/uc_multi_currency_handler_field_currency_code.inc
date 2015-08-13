<?php

class uc_multi_currency_handler_field_currency_code extends views_handler_field {

  /**
   * Constructor.
   */
  function construct() {
    parent::construct();
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
   * Overrides views_handler_field::render().
   */
  function render($values) {
    $this->field_alias = 'currency_code';
    $values->{$this->field_alias} = $values->{$this->aliases['currency']};
    return parent::render($values);
  }

}
