<?php

class uc_multi_currency_handler_field_order_total_cost extends views_handler_field {

  /**
   * Constructor.
   */
  function construct() {
    parent::construct();
    $this->additional_fields['order_id'] = 'order_id';
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
    $cost = db_query("SELECT SUM(cost) FROM {uc_order_products} WHERE order_id = :oid", array(':oid' => $values->{$this->aliases['order_id']}))->fetchField();
    $this->field_alias = 'order_cost';
    $values->{$this->field_alias} = $cost;
    $currency = _uc_multi_currency_currency_load($values->{$this->aliases['currency']});
    return uc_multi_currency_format($cost, $currency);
  }

}
