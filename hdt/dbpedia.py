import logging
from hdtconnector import hdtconnector

logger = logging.getLogger('hdt')

REDIRECT_PROP = "http://dbpedia.org/ontology/wikiPageRedirects";
CONCEPT_TITLE_PROP = "http://www.w3.org/2000/01/rdf-schema#label";
DISAMB_PROP = "http://dbpedia.org/ontology/wikiPageDisambiguates";
COMMENT_PROP = "http://www.w3.org/2000/01/rdf-schema#comment";
LABEL_PROP = "http://www.w3.org/2000/01/rdf-schema#label";
RDF_TYPE = "http://www.w3.org/1999/02/22-rdf-syntax-ns#type";
DCTERMS_SUBJ = "http://purl.org/dc/terms/subject";

class DBpedia(object):
  def __init__(self, hdt_file_path):
    self.hdt = hdtconnector.HDTConnector(hdt_file_path)

  def search(self, uri1, uri2, uri3):
    # If we don't find any tripl, we created an exception
    it = self.hdt.search(uri1, uri2, uri3)
    if not it.has_next():
      raise Exception("No content found for %s, %s, %s" % (uri1, uri2, uri3) )
    return it

  def get_definition(self, uri):
    try:
      it = self.search(uri, COMMENT_PROP, "");
      triple = it.next()
      return triple[2] # object
    except Exception as e:
      logger.warning("get_definition: %s" % e)
    return None

  def get_is_redirect(self, from_uri, to_uri):
    try:
      it = self.search(from_uri, REDIRECT_PROP, to_uri)
      return True
    except Exception as e:
      logger.warning("get_is_redirect: %s" %e)
    return False

  def get_dbpedia_categories_of_res(self, uri):
    result = set()
    try:
      it = self.search(uri, DCTERMS_SUBJ, "")
      while it.has_next():
        res = it.next()
        cat = res[2] #object
        result.add(cat)
      return result
    except Exception as e:
      logger.warning("get_dbpedia_categories_of_res: %s" %e)
    return None

  def get_dbpedia_classes_of_res(self, uri):
    result = set()
    try:
      it = self.search(uri, RDF_TYPE, "")
      while it.has_next():
        res = it.next()
        cat = res[2] #object
        result.add(cat)
      return result
    except Exception as e:
      logger.warning("get_dbpedia_classes_of_res %s" % e)
    return None

  def get_dbpedia_labels(self, uri):
    result = set()
    try: 
      it = self.search(uri, LABEL_PROP, "")
      while it.has_next():
        res = it.next()
        lbl = res[2] #object
        if lbl.startswith("\""):
          lbl = lbl[1:]
        if lbl.endswith("\"@en"):
          lbl = lbl[:(len(lbl)-4)];
        result.add(lbl)
      return result
    except Exception as e:
      logger.warning("get_dbpedia_labels: %s" %e)
    return None

  def disambiguation_pages(self, dbpedia_page):
    result = set()
    try:
      it = self.search(dbpedia_page, DISAMB_PROP, "")
      while it.has_next():
        ts = it.next()
        subj = ts[2] #object
        result.add(subj)
      return result
    except Exception as e:
      logger.warning("disambiguation_pages: %s" % e)
    return None

  def get_ambigous_page(self, dbpedia_url):
    try:
      it = self.search("", DISAMB_PROP, dbpedia_url)
      while it.has_next():
        ts = it.next();
        subj = ts[0] #subject
        return subj
    except Exception as e:
      logger.warning("get_ambigous_page: %s" % e)
    return None

  def select_rdfs_comment_of_resource(self, dbpedia_page):
    try:
      it = self.search(dbpedia_page, COMMENT_PROP, "")
      while it.has_next():
        ts = it.next()
        obj = ts[2] #object 
        return obj
    except Exception as e:
      logger.warning("select_rdfs_comment_of_resource: %s" % e)
    return None

  def is_disambiguation_page(self, dbpedia_page):
    try:
      it = self.search(dbpedia_page, DISAMB_PROP, "")
      while it.has_next():
        return True
    except Exception as e:
      logger.warning("is_disambiguation_page: %s" % e)
    return False

  def select_redirected_pages_to(self, dbpedia_page ):
    result = set()
    try:
      it = self.search("", REDIRECT_PROP, dbpedia_page)
      while it.has_next():
        ts = it.next()
        subj = ts[0] #subject
        result.add(subj)
    except Exception as e:
      logger.warning("select_redirected_pages_to: %s" % e)
    return result

  def select_dbpedia_url_of_title(self, title):
    eng_title = "\"" + title + "\"@en";
    try:
      it = self.search("", CONCEPT_TITLE_PROP, eng_title)
      while it.has_next(): 
        ts = it.next();
        subj = ts[0] #subject
        if ( subj.startswith("http://dbpedia.org/resource/") 
          and not subj.startswith("http://dbpedia.org/resource/Category:")) :
          return subj
    except Exception as e:
      logger.warning("Query for title: " + title +"  - returned nothing")
      possible_url = self.get_dbpedia_url_for_title(title)
      try:
        it = self.search(possible_url, "", "")
        if it.has_next():
          return possible_url
      except Exception as e:
        logger.warning("Query for the url: " + possible_url + " - returned nothing")

  def get_dbpedia_url_for_title(self, title):
    result = title.replace(" ", "_")
    return "http://dbpedia.org/resource/" + result

  def is_redirect(self, uri):
    try:
      it = self.search(uri, REDIRECT_PROP, "");
      if it.has_next():
        return True
    except Exception as e:
      logger.warning("is_redirect: %s" % e)
    return False
