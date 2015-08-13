<?php

/**
 * Returns HTML for an Ubercart price with multi-currency.
 * Overrides theme_uc_price().
 *
 * @param $variables
 *   An associative array containing:
 *   - price: numerical price value.
 *   - currency: {uc_multi_currency}.cid currency identifier.
 *   - suffixes: array of suffixes to be attached.
 *
 * @ingroup themeable
 */
function theme_uc_multi_currency_uc_price($variables) {
  $currency = empty($variables['currency']) ? uc_multi_currency_get_currency() : $variables['currency'];
  $currency = _uc_multi_currency_currency_load($currency);
  $output = '<span class="uc-price">'. uc_multi_currency_format($variables['price'], $currency) .'</span>';
  if (!empty($variables['suffixes'])) {
    $output .= ' <span class="price-suffixes">'. implode(' ', $variables['suffixes']) .'</span>';
  }
  return $output;
}

/**
 * Returns HTML for a product price with multi-currency.
 * Overrides theme_uc_product_price().
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array render element containing:
 *     - #value: Price to be formatted.
 *     - #attributes: (optional) Array of attributes to apply to enclosing DIV.
 *     - #title: (optional) Title to be used as label.
 *     - #currency: {uc_multi_currency}.cid currency identifier.
 *
 * @ingroup themeable
 */
function theme_uc_multi_currency_uc_product_price($variables) {
  $element = $variables['element'];
  $price = $element['#value'];
  $attributes = isset($element['#attributes']) ? $element['#attributes'] : array();
  $label = isset($element['#title']) ? $element['#title'] : '';

  if (isset($attributes['class'])) {
    array_unshift($attributes['class'], 'product-info');
  }
  else {
    $attributes['class'] = array('product-info');
  }

  $output = '<div '. drupal_attributes($attributes) .'>';
  if ($label) {
    $output .= '<span class="uc-price-label">'. $label .'</span> ';
  }
  $vars = array('price' => $price);
  if (!empty($element['#suffixes'])) {
    $vars['suffixes'] = $element['#suffixes'];
  }
  if (!empty($element['#currency'])) {
    $vars['currency'] = $element['#currency'];
  }
  $output .= theme('uc_multi_currency_uc_price', $vars);
  $output .= drupal_render_children($element);
  $output .= '</div>';

  return $output;
}

/**
 * Returns HTML for an Ubercart price textfield with multi-currency.
 *
 * @param $variables
 *   An associative array containing, in addition to the standard textfield items:
 *   - #currency: {uc_multi_currency}.cid currency identifier,
 *
 * @see theme_textfield()
 *
 * @ingroup themeable
 */
function theme_uc_multi_currency_uc_price_textfield($variables) {
  static $currencies = array();

  $cid = isset($variables['element']['#currency']) ? $variables['element']['#currency'] : 0;
  if (!isset($currencies[$cid])) {
    $currencies[$cid] = _uc_multi_currency_currency_load($cid);
  }
  $currency = $currencies[$cid];
  if ($currency) {
    if ($currency->prefix) {
      return '<span class="field-prefix">'. $currency->symbol .'</span> '. theme('textfield', $variables);
    }
    else {
      return theme('textfield', $variables) .' <span class="field-prefix">'. $currency->symbol .'</span>';
    }
  }
  return theme('textfield', $variables);
}

/**
 * Returns HTML for the Ubercart product option form.
 * Overrides theme_uc_object_options_form() from uc_attribute.admin.inc.
 *
 * @param $variables
 *   An associative array containing:
 *   - form: A render element representing the form.
 *
 * @see uc_multi_currency_form_uc_object_options_form_alter()
 * @ingroup themeable
 */
function theme_uc_multi_currency_object_options_form($variables) {
  $form = $variables['form'];
  $output = '';

  drupal_add_js('misc/tableselect.js');
  $header = array(
    array('data' => '&nbsp;&nbsp;'. t('Options'), 'class' => array('select-all')),
    t('Default'),
    t('Cost'),
    t('Price'),
    t('Weight'),
    t('List position'),
  );
  $tables = 0;

  if (isset($form['attributes'])) {
    foreach (element_children($form['attributes']) as $key) {
      $attribute = &$form['attributes'][$key];
      $rows = array();
      if (isset($attribute['options'])) {
        foreach (element_children($attribute['options']) as $oid) {
          $option = &$attribute['options'][$oid];
          $option['cost']['#disabled'] = TRUE;
          $option['cost']['#attributes'] = array('readonly' => 'readonly', 'disabled' => 'disabled');
          $option['price']['#disabled'] = TRUE;
          $option['price']['#attributes'] = array('readonly' => 'readonly', 'disabled' => 'disabled');
          $rows[] = array(
            'data' => array(
              drupal_render($option['select']),
              drupal_render($attribute['default'][$oid]),
              drupal_render($option['cost']),
              drupal_render($option['price']),
              drupal_render($option['weight']),
              drupal_render($option['ordering']),
            ),
            'class' => array('draggable'),
          );
        }
      }

      $table_id = 'uc-attribute-option-table-' . $tables++;
      drupal_add_tabledrag($table_id, 'order', 'sibling', 'uc-attribute-option-table-ordering');

      $output .= theme('table', array(
        'header' => $header,
        'rows' => $rows,
        'attributes' => array(
          'class' => array('product_attributes'),
          'id' => $table_id,
        ),
        'caption' => '<h2>'. drupal_render($attribute['name']) .'</h2>',
        'empty' => t('This attribute does not have any options.'),
      ));
    $output .= drupal_render($attribute['aid']);
    $output .= drupal_render($attribute['uc_multi_currency']);
    }
  }

  if (!$tables) {
    if ($form['type']['#value'] == 'product') {
      drupal_set_message(t('This product does not have any attributes.'), 'warning');
    }
    else {
      drupal_set_message(t('This product class does not have any attributes.'), 'warning');
    }
  }

  $output .= drupal_render_children($form);
  return $output;
}

/**
 * Returns HTML for a table with inline textfield elements.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: the element to be rendered
 *
 * @ingroup themeable
 */
function theme_uc_multi_currency_textfield_table($variables) {
  $element = $variables['element'];
  $textfields = $element['textfields'];

  $rows = array();
  if (isset($element['textfields'])) {
    foreach (element_children($element['textfields']) as $key) {
      $textfields = &$element['textfields'][$key];
      $row = array();
      if (isset($textfields)) {
        foreach (element_children($textfields) as $item) {
          $row[] = drupal_render($textfields[$item]);
        }
      }
      $rows[] = $row;
    }
  }

  return theme('table', array(
    'header' => $element['#header'],
    'rows' => $rows,
    'empty' => isset($element['#empty']) ? $element['#empty'] : '',
    'caption' => isset($element['#caption']) ? $element['#caption'] : '',
    'attributes' => isset($element['#attributes']) ? $element['#attributes'] : array(),
    'sticky' => isset($element['#sticky']) ? $element['#sticky'] : FALSE,
  ));
}
